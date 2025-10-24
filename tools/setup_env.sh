#!/usr/bin/env bash
set -euo pipefail

# ECOS Embedded SDK 环境自动安装脚本
# 
# 功能：
# - 🔍 检测本地ZIP包，避免重复下载
# - 📦 安装主机依赖 (gcc/g++/make, flex/bison, ncurses)
# - 🛠️  安装/配置 RISC-V 交叉工具链
# - 🔧 构建 kconfig 和 fixdep 辅助工具
# - 📝 写入 .envrc (PATH)
#
# 使用：
#   bash tools/setup_env.sh                # 默认下载ZIP工具链
#   bash tools/setup_env.sh --toolchain apt  # 使用apt安装工具链
#
# 注：apt 安装需要sudo权限；ZIP下载需要网络与unzip。

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")"/.. && pwd)"
TOOLS_DIR="$ROOT_DIR/tools"
RISCV_DIR="$TOOLS_DIR/riscv"
RISCV_BIN="$RISCV_DIR/bin"

TOOLCHAIN_SOURCE="zip"  # 默认下载项目提供的riscv.zip
if [[ ${1:-} == "--toolchain" ]]; then
  TOOLCHAIN_SOURCE="${2:-zip}"
elif [[ ${1:-} == "--toolchain=apt" ]]; then
  TOOLCHAIN_SOURCE="apt"
elif [[ ${1:-} == "--toolchain=zip" ]]; then
  TOOLCHAIN_SOURCE="zip"
fi

log() { echo -e "\033[1;32m[setup]\033[0m $*"; }
warn() { echo -e "\033[1;33m[warn ]\033[0m $*"; }
err() { echo -e "\033[1;31m[error]\033[0m $*"; }

ensure_dir() { mkdir -p "$1"; }

install_base_deps() {
  local base_pkgs=(build-essential flex bison libncurses-dev wget unzip git)
  if command -v apt-get >/dev/null 2>&1; then
    log "安装基础依赖包 ..."
    if [[ $EUID -ne 0 ]]; then
      sudo apt-get update -y
      sudo apt-get install -y "${base_pkgs[@]}"
    else
      apt-get update -y
      apt-get install -y "${base_pkgs[@]}"
    fi
  else
    warn "未检测到apt-get，请手动安装基础依赖：${base_pkgs[*]}"
  fi
}

apt_install() {
  local riscv_pkgs=(
    gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
    gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf
  )
  if command -v apt-get >/dev/null 2>&1; then
    log "安装RISC-V工具链依赖 (apt) ..."
    if [[ $EUID -ne 0 ]]; then
      sudo apt-get install -y "${riscv_pkgs[@]}"
    else
      apt-get install -y "${riscv_pkgs[@]}"
    fi
  else
    err "未检测到apt-get，请使用 --toolchain zip 或在本机手动安装依赖。"
    exit 1
  fi
}

check_zip_exists() {
  local zip_path="$TOOLS_DIR/riscv.zip"
  local extracted_dir="$RISCV_DIR"
  
  # 检查是否已有解压的工具链目录且包含必要文件
  if [[ -d "$extracted_dir/bin" ]] && [[ -x "$extracted_dir/bin/riscv32-unknown-elf-gcc" ]]; then
    log "检测到已安装的RISC-V工具链：$extracted_dir"
    return 0  # 已存在，无需重新安装
  fi
  
  # 检查是否有本地ZIP文件
  if [[ -f "$zip_path" ]]; then
    log "检测到本地ZIP包：$zip_path"
    local file_size=$(stat -c%s "$zip_path" 2>/dev/null || echo "0")
    if [[ $file_size -gt 1048576 ]]; then  # 大于1MB认为是有效文件
      log "使用本地ZIP包进行安装"
      return 1  # 有本地文件，需要解压
    else
      warn "本地ZIP文件过小，可能损坏，将重新下载"
      rm -f "$zip_path"
    fi
  fi
  
  return 2  # 需要下载
}

install_toolchain_zip() {
  ensure_dir "$TOOLS_DIR"
  local url="https://github.com/ecoslab/ecos-embed-sdk/releases/download/riscv-tools/riscv.zip"
  local zip_path="$TOOLS_DIR/riscv.zip"
  
  local zip_status
  set +e  # 临时禁用 set -e
  check_zip_exists
  zip_status=$?
  set -e  # 重新启用 set -e
  log "zip_status $zip_status" 
  case $zip_status in
    0)
      log "RISC-V工具链已安装，跳过下载"
      return 0
      ;;
    1)
      log "使用本地ZIP包解压到：$RISCV_DIR"
      ;;
    2)
      log "下载 RISC-V 工具链 (ZIP)：$url"
      if ! wget -O "$zip_path" "$url"; then
        err "下载失败，请检查网络连接或手动下载到：$zip_path"
        exit 1
      fi
      log "下载完成，解压到：$RISCV_DIR"
      ;;
  esac
  
  # 解压ZIP包
  if [[ $zip_status -ne 0 ]]; then
    rm -rf "$RISCV_DIR"
    if ! unzip -q "$zip_path" -d "$TOOLS_DIR"; then
      err "解压失败，ZIP文件可能损坏"
      rm -f "$zip_path"
      exit 1
    fi
    chmod -R +x "$RISCV_DIR" || true
    log "RISC-V工具链安装完成"
  fi
}

link_riscv32_aliases() {
  # 为src/Makefile的 riscv32-unknown-elf-* 前缀提供别名，指向系统的 riscv64-unknown-elf-*
  ensure_dir "$RISCV_BIN"
  local tools=(gcc g++ ar as ld objcopy objdump ranlib size strip)
  for t in "${tools[@]}"; do
    if command -v "riscv64-unknown-elf-$t" >/dev/null 2>&1; then
      ln -sf "$(command -v riscv64-unknown-elf-$t)" "$RISCV_BIN/riscv32-unknown-elf-$t"
    else
      warn "未找到 riscv64-unknown-elf-$t，可使用 --toolchain zip 安装自带版本。"
    fi
  done
}

write_envrc() {
  log "写入 .envrc 环境变量"
  
  # 根据工具链类型决定是否设置 PATH
  if [[ "$TOOLCHAIN_SOURCE" == "system" ]]; then
    # 使用系统工具链，不修改 PATH，也不需要设置 ECOS_HOME（Makefile 会动态获取）
    cat >"$ROOT_DIR/.envrc" <<EOF
# 自动生成：ECOS Embedded SDK 环境
EOF
  else
    # 使用项目工具链，设置 PATH，ECOS_HOME 仍在 Makefile 中动态获取
    cat >"$ROOT_DIR/.envrc" <<EOF
# 自动生成：ECOS Embedded SDK 环境
# 优先使用项目 tools/riscv/bin (ZIP或apt别名)
export PATH="$RISCV_BIN:\$PATH"
EOF
  fi
}

build_helpers() {
  log "构建 fixdep 与 kconfig 工具"
  make -s -C "$TOOLS_DIR/fixdep" || { err "构建 fixdep 失败"; exit 1; }
  make -s -C "$TOOLS_DIR/kconfig" NAME=conf || { err "构建 kconfig(conf) 失败"; exit 1; }
  make -s -C "$TOOLS_DIR/kconfig" NAME=mconf || { err "构建 kconfig(mconf) 失败"; exit 1; }
}

summary_next() {
  cat <<EOF

✅ 依赖安装完成。后续建议：

🔧 加载环境变量：
   source "$ROOT_DIR/.envrc"    # 或安装 direnv 后执行：direnv allow

⚙️  运行配置菜单：
   make -C "$ROOT_DIR/src" menuconfig

🔨 编译固件：
   make -C "$ROOT_DIR/src"

📋 验证工具链：
   riscv32-unknown-elf-gcc --version
   riscv64-unknown-elf-gcc --version

🚀 (可选) 编译 Abstract-Machine 示例：
   export OBJDUMP="riscv64-unknown-elf-objdump"; export OBJCOPY="riscv64-unknown-elf-objcopy"
   # 具体目标依赖于项目脚本，可参考 utils/abstract-machine/scripts/riscv32-xxh.mk

EOF
}

ask_user_toolchain_choice() {
  # 如果是非交互模式或已指定工具链源，跳过询问
  if [[ "$TOOLCHAIN_SOURCE" == "apt" ]] || [[ ! -t 0 ]]; then
    return 0
  fi
  
  echo
  log "RISC-V 工具链安装选项："
  echo "  1) 使用 SDK 预编译工具链 (riscv32-unknown-elf-*) [推荐]"
  echo "  2) 使用系统工具链 (需要手动配置 Makefile)"
  echo
  
  while true; do
    read -p "请选择 [1/2] (默认: 1): " choice
    case "${choice:-1}" in
      1)
        log "将安装 SDK 预编译工具链"
        return 0
        ;;
      2)
        echo
        warn "您选择了使用系统工具链。"
        warn "请手动修改 src/Makefile 中的 CROSS 变量："
        warn "  当前: CROSS=riscv32-unknown-elf-"
        warn "  建议: CROSS=riscv64-unknown-elf-  (或您系统中的工具链前缀)"
        echo
        log "修改完成后，您可以："
        log "  1) 使用 apt 安装系统工具链: bash tools/setup_env.sh --toolchain apt"
        log "  2) 或者直接使用系统已安装的工具链进行编译"
        echo
        log "脚本将继续配置环境变量和构建辅助工具..."
        TOOLCHAIN_SOURCE="system"  # 标记为使用系统工具链
        return 0
        ;;
      *)
        echo "请输入 1 或 2"
        ;;
    esac
  done
}

main() {
  log "项目根目录：$ROOT_DIR"
  ensure_dir "$RISCV_BIN"

  # 首先安装基础依赖（wget, unzip等）
  install_base_deps

  if [[ "$TOOLCHAIN_SOURCE" == "apt" ]]; then
    apt_install
    link_riscv32_aliases
  elif [[ "$TOOLCHAIN_SOURCE" == "system" ]]; then
    log "跳过工具链安装，使用系统工具链"
  else
    # 询问用户是否使用 SDK 预编译工具链
    ask_user_toolchain_choice
    # 如果用户选择了 SDK 工具链，则安装
    if [[ "$TOOLCHAIN_SOURCE" != "system" ]]; then
      install_toolchain_zip
    fi
  fi

  write_envrc
  build_helpers
  summary_next
  log "环境安装与配置完成"
}

main "$@"

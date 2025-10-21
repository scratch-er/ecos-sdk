#!/usr/bin/env bash
set -euo pipefail

# ECOS Embedded SDK 环境自动安装脚本
# - 安装主机依赖 (gcc/g++/make, flex/bison, ncurses)
# - 安装/配置 RISC-V 交叉工具链
# - 构建 kconfig 和 fixdep 辅助工具
# - 写入 .envrc (ECOS_HOME/AM_HOME/PATH)
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
AM_DIR="$ROOT_DIR/utils/abstract-machine"

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

apt_install() {
  local pkgs=(
    build-essential flex bison libncurses-dev wget unzip git
    gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
    gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf
  )
  if command -v apt-get >/dev/null 2>&1; then
    log "安装主机与RISC-V工具链依赖 (apt) ..."
    if [[ $EUID -ne 0 ]]; then
      sudo apt-get update -y
      sudo apt-get install -y "${pkgs[@]}"
    else
      apt-get update -y
      apt-get install -y "${pkgs[@]}"
    fi
  else
    err "未检测到apt-get，请使用 --toolchain zip 或在本机手动安装依赖。"
    exit 1
  fi
}

install_toolchain_zip() {
  ensure_dir "$TOOLS_DIR"
  local url="https://github.com/ecoslab/ecos-embed-sdk/releases/download/riscv-tools/riscv.zip"
  local zip_path="$TOOLS_DIR/riscv.zip"
  log "下载 RISC-V 工具链 (ZIP)：$url"
  wget -O "$zip_path" "$url"
  log "解压到：$RISCV_DIR"
  rm -rf "$RISCV_DIR"
  unzip -q "$zip_path" -d "$TOOLS_DIR"
  chmod -R +x "$RISCV_DIR" || true
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
  cat >"$ROOT_DIR/.envrc" <<EOF
# 自动生成：ECOS Embedded SDK 环境
export ECOS_HOME="$ROOT_DIR"
export AM_HOME="$AM_DIR"
# 优先使用项目 tools/riscv/bin (ZIP或apt别名)
export PATH="$RISCV_BIN:\$PATH"
EOF
}

build_helpers() {
  log "构建 fixdep 与 kconfig 工具"
  make -s -C "$TOOLS_DIR/fixdep" || { err "构建 fixdep 失败"; exit 1; }
  make -s -C "$TOOLS_DIR/kconfig" NAME=conf || { err "构建 kconfig(conf) 失败"; exit 1; }
  make -s -C "$TOOLS_DIR/kconfig" NAME=mconf || { err "构建 kconfig(mconf) 失败"; exit 1; }
}

summary_next() {
  cat <<EOF

依赖安装完成。后续建议：
- 加载环境变量：
  source "$ROOT_DIR/.envrc"    # 或安装 direnv 后执行：direnv allow
- 运行配置菜单：
  make -C "$ROOT_DIR/src" menuconfig
- 编译固件：
  make -C "$ROOT_DIR/src"
- (可选) 编译 Abstract-Machine 示例：
  export OBJDUMP="riscv64-unknown-elf-objdump"; export OBJCOPY="riscv64-unknown-elf-objcopy"
  # 具体目标依赖于项目脚本，可参考 utils/abstract-machine/scripts/riscv32-xxh.mk

EOF
}

main() {
  log "项目根目录：$ROOT_DIR"
  ensure_dir "$RISCV_BIN"

  if [[ "$TOOLCHAIN_SOURCE" == "apt" ]]; then
    apt_install
    link_riscv32_aliases
  else
    # 默认使用项目提供的ZIP工具链，以匹配 riscv32-unknown-elf-* 前缀
    install_toolchain_zip
  fi

  write_envrc
  build_helpers
  summary_next
  log "环境安装与配置完成"
}

main "$@"
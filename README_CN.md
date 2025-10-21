# ECOS 嵌入式 SDK

## 快速开始

### 1. 环境配置

#### 方式一：使用脚本自动配置（推荐）
```bash
bash tools/setup_env.sh
```

#### 方式二：手动配置

##### 步骤1：安装基础依赖包
```bash
# Ubuntu/Debian 系统
sudo apt-get update -y
sudo apt-get install -y build-essential flex bison libncurses-dev wget unzip git
```

##### 步骤2：安装 RISC-V 交叉编译工具链

**选项A：下载预编译工具链（推荐）**
```bash
# 创建工具目录
mkdir -p tools

# 下载工具链ZIP包
wget -O tools/riscv.zip https://github.com/ecoslab/ecos-embed-sdk/releases/download/riscv-tools/riscv.zip

# 解压到tools目录
unzip -q tools/riscv.zip -d tools/

# 设置执行权限
chmod -R +x tools/riscv/
```

**选项B：使用系统包管理器安装**
```bash
# 安装RISC-V工具链
sudo apt-get install -y gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu \
                        gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf

# 创建符号链接（为了兼容项目中的riscv32前缀）
mkdir -p tools/riscv/bin
for tool in gcc g++ ar as ld objcopy objdump ranlib size strip; do
    ln -sf $(which riscv64-unknown-elf-$tool) tools/riscv/bin/riscv32-unknown-elf-$tool
done
```

##### 步骤3：配置环境变量
```bash
# 设置项目环境变量
export ECOS_HOME="$(pwd)"
export AM_HOME="$(pwd)/utils/abstract-machine"
export PATH="$(pwd)/tools/riscv/bin:$PATH"

# 将环境变量写入.envrc文件（可选，用于direnv）
cat > .envrc << EOF
# ECOS Embedded SDK 环境变量
export ECOS_HOME="$(pwd)"
export AM_HOME="$(pwd)/utils/abstract-machine"
export PATH="$(pwd)/tools/riscv/bin:\$PATH"
EOF
```

##### 步骤4：构建辅助工具
```bash
# 构建fixdep工具
make -C tools/fixdep

# 构建kconfig工具
make -C tools/kconfig NAME=conf
make -C tools/kconfig NAME=mconf
```

##### 步骤5：验证安装
```bash
# 检查环境变量
echo "ECOS_HOME: $ECOS_HOME"
echo "AM_HOME: $AM_HOME"
echo "PATH包含: $(echo $PATH | grep -o '[^:]*riscv[^:]*')"

# 验证工具链
riscv32-unknown-elf-gcc --version
riscv64-unknown-elf-gcc --version

# 测试编译工具
make -C tools/fixdep clean && make -C tools/fixdep
make -C tools/kconfig clean && make -C tools/kconfig NAME=conf
```

### 2. 创建配置文件
```bash
cd src
make menuconfig  // 打开配置界面，默认配置退出即可
```

### 3. 编译固件
```bash
cd src
make
```

在`src/build`目录下生成文件：
- `retrosoc_fw.elf` - 可执行文件
- `retrosoc_fw.hex` - Verilog仿真文件
- `retrosoc_fw.bin` - 烧录文件

## 文档

详细的开发指南请参考各模块驱动文档：
- [GPIO 驱动](docs/gpio_api.md)
- [QSPI 驱动](docs/qspi_api.md)
- [I2C 驱动](docs/i2c_api.md)
- [PWM 驱动](docs/pwm_api.md)
- [timer 驱动](docs/timer_api.md)
- [ST7735 驱动](docs/st7735_api.md)

## 致谢

- 【代码编写】 [maksyuki](https://github.com/maksyuki/maksyuki)
- 【整理维护 & 代码编写】 [XHTimmo](https://github.com/XHTimmo)
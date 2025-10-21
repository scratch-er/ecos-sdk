# ECOS 嵌入式 SDK

## 快速开始

### 1. 环境配置
下载并配置 [RISC-V 交叉编译工具链](https://github.com/ecoslab/ecos-embed-sdk/releases/download/riscv-tools/riscv.zip)：
```bash
# 下载工具链到 tools 目录
# 添加到环境变量
export PATH=$PATH:/path/to/ECOS_env/tools/riscv/bin
# 同时修改该路径的文件权限 需要 +x
chmod -R +x /path/to/ECOS_env/tools/riscv/
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
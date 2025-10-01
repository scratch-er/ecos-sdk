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

### 2. 编译固件
```bash
cd src
make
```

生成文件：
- `retrosoc_fw.elf` - 可执行文件
- `retrosoc_fw.hex` - Verilog仿真文件
- `retrosoc_fw.bin` - 烧录文件

## 文档

详细的开发指南请参考：[开发入门指南](doc/开发入门指南.md)

## 致谢

- 【代码编写】 [maksyuki](https://github.com/maksyuki/maksyuki)
- 【整理维护】 [XHTimmo](https://github.com/XHTimmo)
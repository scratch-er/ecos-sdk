# ECOS Embedded SDK

- 【中文文档】 [README_CN.md](README_CN.md)
## Fast Start

### 1. Environment Setup
Download and set up the RISC-V cross-compilation toolchain:
```bash
# Download the toolchain to the tools directory
# Add to environment variables
export PATH=$PATH:/path/to/ECOS_env/tools/riscv/bin
# Make sure to add execute permissions to the toolchain directory
```

### 2. Compile Firmware
```bash
cd src
make
```

Generated files:
- `retrosoc_fw.elf` - Executable file
- `retrosoc_fw.hex` - Verilog simulation file
- `retrosoc_fw.bin` - Burnable file

## Documentation

For detailed development guidelines, please refer to: [Development Guide](doc/Development_Guide.md)

## Acknowledgments

- 【Code Writing】 [maksyuki](https://github.com/maksyuki/maksyuki)
- 【Maintenance】 [XHTimmo](https://github.com/XHTimmo)

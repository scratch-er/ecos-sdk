# ECOS Embedded SDK

- 【中文文档】 [README_CN.md](README_CN.md)
## Fast Start

### 1. Environment Setup

#### Method 1: Automated Setup with Script (Recommended)
```bash
bash tools/setup_env.sh
```

#### Method 2: Manual Setup

##### Step 1: Install Basic Dependencies
```bash
# Ubuntu/Debian systems
sudo apt-get update -y
sudo apt-get install -y build-essential flex bison libncurses-dev wget unzip git
```

##### Step 2: Install RISC-V Cross-Compilation Toolchain

**Option A: Download Pre-compiled Toolchain (Recommended)**
```bash
# Create tools directory
mkdir -p tools

# Download toolchain ZIP package
wget -O tools/riscv.zip https://github.com/ecoslab/ecos-embed-sdk/releases/download/riscv-tools/riscv.zip

# Extract to tools directory
unzip -q tools/riscv.zip -d tools/

# Set execute permissions
chmod -R +x tools/riscv/
```

**Option B: Install via System Package Manager**
```bash
# Install RISC-V toolchain
sudo apt-get install -y gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu \
                        gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf

# Create symbolic links (for compatibility with riscv32 prefix used in project)
mkdir -p tools/riscv/bin
for tool in gcc g++ ar as ld objcopy objdump ranlib size strip; do
    ln -sf $(which riscv64-unknown-elf-$tool) tools/riscv/bin/riscv32-unknown-elf-$tool
done
```

##### Step 3: Configure Environment Variables
```bash
# Set project environment variables
export ECOS_HOME="$(pwd)"
export AM_HOME="$(pwd)/utils/abstract-machine"
export PATH="$(pwd)/tools/riscv/bin:$PATH"

# Write environment variables to .envrc file (optional, for direnv)
cat > .envrc << EOF
# ECOS Embedded SDK Environment Variables
export ECOS_HOME="$(pwd)"
export AM_HOME="$(pwd)/utils/abstract-machine"
export PATH="$(pwd)/tools/riscv/bin:\$PATH"
EOF
```

##### Step 4: Build Helper Tools
```bash
# Build fixdep tool
make -C tools/fixdep

# Build kconfig tools
make -C tools/kconfig NAME=conf
make -C tools/kconfig NAME=mconf
```

##### Step 5: Verify Installation
```bash
# Check environment variables
echo "ECOS_HOME: $ECOS_HOME"
echo "AM_HOME: $AM_HOME"
echo "PATH contains: $(echo $PATH | grep -o '[^:]*riscv[^:]*')"

# Verify toolchain
riscv32-unknown-elf-gcc --version
riscv64-unknown-elf-gcc --version

# Test build tools
make -C tools/fixdep clean && make -C tools/fixdep
make -C tools/kconfig clean && make -C tools/kconfig NAME=conf
```

### 2. Create Configuration File
```bash
cd src
make menuconfig
```

### 3. Compile Firmware
```bash
cd src
make
```

Generated files:
- `retrosoc_fw.elf` - Executable file
- `retrosoc_fw.hex` - Verilog simulation file
- `retrosoc_fw.bin` - Burnable file

## Documentation

For detailed development guidelines, please refer to: [Development Guide](docs/development_guide.md)

## Acknowledgments

- 【Code Writing】 [maksyuki](https://github.com/maksyuki/maksyuki)
- 【Maintenance & Code Writing】 [XHTimmo](https://github.com/XHTimmo)

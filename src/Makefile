# retroSoC 固件构建脚本
# 用于编译基于RISC-V架构的嵌入式固件

# RISC-V 交叉编译工具链前缀
CROSS=riscv32-unknown-elf-
BUILD_DIR := build

# 包含配置文件
-include configs/.config
# 编译器标志配置
# -mabi=ilp32: 使用ILP32 ABI
# -march=rv32im: RV32I基础指令集 + M乘除法扩展
# -ffreestanding: 独立环境编译
# -nostdlib: 不链接标准库
CFLAGS := -mabi=ilp32 \
	  -march=rv32im \
	  -Wl,-Bstatic,-T,$(BUILD_DIR)/retrosoc_sections.lds,--strip-debug \
	  -ffreestanding \
	  -nostdlib

# 根据配置文件添加编译优化选项
ifdef CONFIG_BUILD_OPT_FLAGS
CFLAGS += $(subst ",,$(CONFIG_BUILD_OPT_FLAGS))
endif

# 根据配置文件添加调试选项
ifdef CONFIG_BUILD_DEBUG
CFLAGS += -g -DDEBUG
endif

# 根据配置文件添加详细输出选项
ifdef CONFIG_BUILD_VERBOSE
VERBOSE := 1
endif

# 固件名称 - 从配置文件读取，如果未定义则使用默认值
ifdef CONFIG_FIRMWARE_NAME
FIRMWARE_NAME := $(subst ",,$(CONFIG_FIRMWARE_NAME))
else
FIRMWARE_NAME := main
endif

# 源文件列表
SRC_PATH := ./start.s ./main.c \
		./components/libc/src/string.c \
		./components/libc/src/stdio.c \
		./components/libgcc/src/div.S \
		./components/libgcc/src/muldi3.S \
		./components/libgcc/src/mulsi3.c \
		./components/libgcc/src/lshrdi3.c \
		./components/sys_uart/src/sys_uart.c \
		./components/gpio/src/gpio.c \
		./components/qspi/src/qspi.c \
		./components/timer/src/timer.c \
		./components/pwm/src/pwm.c \
		./components/i2c/src/i2c.c \
		./components/hp_uart/src/hp_uart.c \
		./devices/st7735/src/st7735.c \
		./devices/gy_sgp30/src/sgp30.c \


CFLAGS += -I./configs \
		-I./components/libc/include \
		-I./components/libgcc/include \
		-I./components/sys_uart/include \
		-I./components/gpio/include \
		-I./components/qspi/include \
		-I./components/timer/include \
		-I./components/pwm/include \
		-I./components/i2c/include \
		-I./components/hp_uart/include \
		-I./devices/st7735/include \
		-I./devices/gy_sgp30/include \
		
# 链接脚本路径
LDS_PATH := ./sections.lds

# 主要构建目标：生成固件的所有格式文件
$(FIRMWARE_NAME):
	@mkdir -p $(BUILD_DIR)
	$(CROSS)cpp -P -o $(BUILD_DIR)/retrosoc_sections.lds $(LDS_PATH)
	$(CROSS)gcc $(CFLAGS) -I./ -o $(BUILD_DIR)/$@ $(SRC_PATH)
	$(CROSS)objcopy -O verilog $(BUILD_DIR)/$@ $(BUILD_DIR)/$(FIRMWARE_NAME).hex
	sed -i 's/@30000000/@00000000/g' $(BUILD_DIR)/$(FIRMWARE_NAME).hex
	$(CROSS)objcopy -O binary  $(BUILD_DIR)/$@ $(BUILD_DIR)/$(FIRMWARE_NAME).bin
	$(CROSS)objdump -d $(BUILD_DIR)/$@ > $(BUILD_DIR)/$(FIRMWARE_NAME).txt

# 清理构建产物
clean:
	rm -rf $(BUILD_DIR)

clean_config:
	rm -rf configs/generated configs/config configs/.config configs/.config.old
	
clean_all:
	rm -rf $(BUILD_DIR) 
	rm -rf configs/generated configs/config configs/.config configs/.config.old
	rm -rf $(ECOS_HOME)/tools/fixdep/build
	rm -rf $(ECOS_HOME)/tools/kconfig/build

include scripts/config.mk
# 声明伪目标
.PHONY: $(FIRMWARE_NAME).elf clean

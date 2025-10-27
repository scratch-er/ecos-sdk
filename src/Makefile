# retroSoC 固件构建脚本
# 用于编译基于RISC-V架构的嵌入式固件

# RISC-V 交叉编译工具链前缀
CROSS := riscv32-unknown-elf-
CC := $(CROSS)gcc
AR := $(CROSS)ar
LD := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy
OBJDUMP := $(CROSS)objdump
BUILD_DIR := build

# 包含配置文件
-include configs/.config

# 编译器标志配置
# -mabi=ilp32: 使用ILP32 ABI
# -march=rv32im: RV32I基础指令集 + M乘除法扩展
# -ffreestanding: 独立环境编译
# -nostdlib: 不链接标准库
CFLAGS := -mabi=ilp32 -march=rv32im -ffreestanding -nostdlib
LDFLAGS := -Bstatic -melf32lriscv_ilp32 -T sections.lds

# 根据配置文件添加编译优化选项
ifdef CONFIG_BUILD_OPT_FLAGS
CFLAGS += $(subst ,,$(CONFIG_BUILD_OPT_FLAGS))
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
FIRMWARE_NAME := $(subst ,,$(CONFIG_FIRMWARE_NAME))
else
FIRMWARE_NAME := main
endif

# 添加头文件包含路径
CFLAGS += -I./configs -I.
CFLAGS += $(addprefix -I,$(wildcard components/*/include))
CFLAGS += $(addprefix -I,$(wildcard devices/*/include))

OBJ_DIR=$(BUILD_DIR)/obj

# 静态库源文件列表
LIB_SRCS += $(shell find components -iname '*.c')
LIB_SRCS += $(shell find devices -iname '*.c')
LIB_OBJS += $(OBJ_DIR)/start.o
LIB_OBJS += $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))

# 主要构建目标：生成固件的所有格式文件
all: $(BUILD_DIR)/$(FIRMWARE_NAME).bin $(BUILD_DIR)/$(FIRMWARE_NAME).hex $(BUILD_DIR)/$(FIRMWARE_NAME).txt

# C语言文件构建规则
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# 汇编代码构建规则
$(OBJ_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# 静态库的构建规则
STATIC_LIB := $(BUILD_DIR)/libecossdk.a
$(STATIC_LIB): $(LIB_OBJS)
	rm -f $@
	$(AR) rcs $@ $(LIB_OBJS)

# BIN镜像文件的构建规则
%.bin:%.elf
	$(OBJCOPY) -O binary --only-section .text $< $@

# HEX镜像文件的构建规则
%.hex:%.elf
	$(OBJCOPY) -O verilog --only-section .text $< $@
	sed -i 's/@30000000/@00000000/g' $@

# TXT内存映射的构建规则
%.txt:%.elf
	$(OBJDUMP) -d $< > $@

# 链接脚本路径
LDS_PATH := ./sections.lds

# 使用main.c构建固件
$(BUILD_DIR)/$(FIRMWARE_NAME).elf: $(OBJ_DIR)/main.o $(STATIC_LIB) $(LDS_PATH)
	$(LD) $(LDFLAGS) $(OBJ_DIR)/main.o $(STATIC_LIB) -o $@

# 构建所有示例
EXAMPLE_SRCS := $(wildcard example/*/main.c)
EXAMPLE_OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(EXAMPLE_SRCS))
EXMAPLE_ELFS := $(patsubst example/%/main.c,$(BUILD_DIR)/example/%.elf,$(EXAMPLE_SRCS))
EXMAPLE_BINS := $(patsubst example/%/main.c,$(BUILD_DIR)/example/%.bin,$(EXAMPLE_SRCS))
EXMAPLE_HEXS := $(patsubst example/%/main.c,$(BUILD_DIR)/example/%.hex,$(EXAMPLE_SRCS))
EXMAPLE_TXTS := $(patsubst example/%/main.c,$(BUILD_DIR)/example/%.txt,$(EXAMPLE_SRCS))

$(BUILD_DIR)/example/%.elf: $(OBJ_DIR)/example/%/main.o $(STATIC_LIB) $(LDS_PATH)
	mkdir -p $(BUILD_DIR)/example
	$(LD) $(LDFLAGS) $< $(STATIC_LIB) -o $@

example: $(EXMAPLE_ELFS) $(EXMAPLE_BINS) $(EXMAPLE_HEXS) $(EXMAPLE_TXTS)

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

-include scripts/config.mk

# 声明伪目标
.PHONY: all clean clean_config clean_all example

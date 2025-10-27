COREMARK_SRCS += example/coremark/core_list_join.c
COREMARK_SRCS += example/coremark/core_main.c
COREMARK_SRCS += example/coremark/core_matrix.c
COREMARK_SRCS += example/coremark/core_state.c
COREMARK_SRCS += example/coremark/core_util.c
COREMARK_SRCS += example/coremark/core_portme.c

COREMARK_OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(COREMARK_SRCS))
$(BUILD_DIR)/example/coremark.elf: $(COREMARK_OBJS) $(OBJ_DIR)/start.o $(STATIC_LIB) $(LDS_PATH)
	mkdir -p $(BUILD_DIR)/example
	$(LD) $(LDFLAGS) $(OBJ_DIR)/start.o $(COREMARK_OBJS) $(STATIC_LIB) -o $@

$(EXMAPLE_ELFS) += $(BUILD_DIR)/example/coremark.elf
$(EXMAPLE_BINS) += $(BUILD_DIR)/example/coremark.bin
$(EXMAPLE_HEXS) += $(BUILD_DIR)/example/coremark.hex
$(EXMAPLE_TXTS) += $(BUILD_DIR)/example/coremark.txt

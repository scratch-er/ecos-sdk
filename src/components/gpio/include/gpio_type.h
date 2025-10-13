#include "stdint.h"

/* ========== GPIO 寄存器组 ========== */
#define REG_GPIO_DATA         (*(volatile uint32_t*)0x03000000)  // GPIO数据寄存器
#define REG_GPIO_ENB          (*(volatile uint32_t*)0x03000004)  // GPIO使能寄存器
#define REG_GPIO_PUB          (*(volatile uint32_t*)0x03000008)  // GPIO上拉使能寄存器
#define REG_GPIO_PDB          (*(volatile uint32_t*)0x0300000c)  // GPIO下拉使能寄存器

typedef enum {
    GPIO_NUM_0 = 0,
    GPIO_NUM_1 = 1,
    GPIO_NUM_2 = 2,
    GPIO_NUM_3 = 3,
    GPIO_NUM_4 = 4,
    GPIO_NUM_5 = 5,
    GPIO_NUM_6 = 6,
    GPIO_NUM_7 = 7,
    GPIO_NUM_8 = 8,
    GPIO_NUM_9 = 9,
    GPIO_NUM_10 = 10,
    GPIO_NUM_11 = 11,
    GPIO_NUM_12 = 12,
    GPIO_NUM_13 = 13,
    GPIO_NUM_14 = 14,
    GPIO_NUM_15 = 15,
} gpio_num_t;

typedef enum{
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT = 1,
} gpio_mode_t;

typedef enum{
    GPIO_LEVEL_LOW = 0,
    GPIO_LEVEL_HIGH = 1,
} gpio_level_t;

typedef struct {
    uint32_t pin_bit_mask; // 引脚位掩码，用于设置或读取多个引脚
    gpio_mode_t mode; // GPIO模式，输入或输出
} gpio_config_t;
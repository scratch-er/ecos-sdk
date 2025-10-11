/*
 * GPIO 驱动头文件
 * 定义GPIO相关的函数接口
 */

#ifndef TINYGPIO_H__
#define TINYGPIO_H__

#include "tinygpio_type.h"

typedef struct {
    uint64_t pin_bit_mask; // 引脚位掩码，用于设置或读取多个引脚
    gpio_mode_t mode; // GPIO模式，输入或输出
} gpio_config_t;
/**
 * @brief GPIO功能测试函数
 * 
 * 执行完整的GPIO功能测试，包括：
 * - 寄存器读写测试
 * - LED输出控制测试
 * - 按键输入检测测试
 */
void ip_gpio_test();

void gpio_config(const gpio_config_t* config);

#endif
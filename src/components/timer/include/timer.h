#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/* ========== 定时器0 寄存器组 ========== */
#define REG_TIM0_CONFIG       (*(volatile uint32_t*)0x0300005c)  // 定时器0配置寄存器
#define REG_TIM0_VALUE        (*(volatile uint32_t*)0x03000060)  // 定时器0计数值寄存器
#define REG_TIM0_DATA         (*(volatile uint32_t*)0x03000064)  // 定时器0数据寄存器

void delay_us(uint32_t val);
void delay_ms(uint32_t val);
void delay_s(uint32_t val);
#endif
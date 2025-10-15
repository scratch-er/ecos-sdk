#ifndef __PWM_TYPE_H__
#define __PWM_TYPE_H__

#include <stdint.h>

/* ========== PWM 寄存器组 ========== */
#define REG_CUST_PWM_CTRL     (*(volatile uint32_t*)0x03004000)  // PWM控制寄存器
#define REG_CUST_PWM_PSCR     (*(volatile uint32_t*)0x03004004)  // PWM预分频寄存器
#define REG_CUST_PWM_CNT      (*(volatile uint32_t*)0x03004008)  // PWM计数寄存器
#define REG_CUST_PWM_CMP      (*(volatile uint32_t*)0x0300400c)  // PWM比较寄存器
#define REG_CUST_PWM_CR0      (*(volatile uint32_t*)0x03004010)  // PWM通道0比较寄存器
#define REG_CUST_PWM_CR1      (*(volatile uint32_t*)0x03004014)  // PWM通道1比较寄存器
#define REG_CUST_PWM_CR2      (*(volatile uint32_t*)0x03004018)  // PWM通道2比较寄存器
#define REG_CUST_PWM_CR3      (*(volatile uint32_t*)0x0300401c)  // PWM通道3比较寄存器
#define REG_CUST_PWM_STAT     (*(volatile uint32_t*)0x03004020)  // PWM状态寄存器

typedef struct {
    uint32_t pscr;
    uint32_t cmp;
} pwm_config_t;

typedef enum {
    PWM_CH0 = 0,
    PWM_CH1 = 1,
    PWM_CH2 = 2,
    PWM_CH3 = 3,
} pwm_channel_t;

#endif
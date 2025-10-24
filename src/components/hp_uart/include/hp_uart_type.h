#ifndef __HP_UART_TYPE_H__
#define __HP_UART_TYPE_H__

#include <stdint.h>
#include <stdbool.h>

#define REG_CUST_UART_LCR     (*(volatile uint32_t*)0x03003000)  // UART线路控制寄存器
#define REG_CUST_UART_DIV     (*(volatile uint32_t*)0x03003004)  // UART分频寄存器
#define REG_CUST_UART_TRX     (*(volatile uint32_t*)0x03003008)  // UART收发寄存器
#define REG_CUST_UART_FCR     (*(volatile uint32_t*)0x0300300c)  // UART FIFO控制寄存器
#define REG_CUST_UART_LSR     (*(volatile uint32_t*)0x03003010)  // UART线路状态寄存器

#endif
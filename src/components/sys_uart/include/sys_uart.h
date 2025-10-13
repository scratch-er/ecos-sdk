#ifndef __SYS_UART_H__
#define __SYS_UART_H__

#include <stdint.h>

#define REG_UART_CLKDIV       (*(volatile uint32_t*)0x03000010)  // UART时钟分频寄存器
#define REG_UART_DATA         (*(volatile uint32_t*)0x03000014)  // UART数据寄存器

void sys_uart_init(void);
void sys_putchar(char c);

#endif
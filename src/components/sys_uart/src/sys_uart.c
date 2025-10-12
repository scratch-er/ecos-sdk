#include "sys_uart.h"

void sys_putchar(char c){
    REG_UART_DATA = c;
}

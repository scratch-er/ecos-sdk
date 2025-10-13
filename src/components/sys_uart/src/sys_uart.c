#include "sys_uart.h"
#include "generated/autoconf.h"

void sys_uart_init(void){
    REG_UART_CLKDIV =  (uint32_t)(72 * 1000000 / 115200);
}

void sys_putchar(char c){
    REG_UART_DATA = c;
}

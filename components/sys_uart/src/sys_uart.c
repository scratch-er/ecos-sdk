#include "sys_uart.h"
#include "generated/autoconf.h"
#include "board.h"

void sys_uart_init(void){
#ifdef CONFIG_STARRYSKY_C1
    REG_UART_CLKDIV =  (uint32_t)(CONFIG_CPU_FREQ_MHZ * 1000000 / 115200);
#elif CONFIG_STARRYSKY_L3
    UART_REG_LC = UART_REG_LC | 0x80;
    UART_REG_TH = 13 ; // 25M 115200bps
    UART_REG_LC = 0x03; // OpenCores UART16550 core spec ver0.6 4.9 section
#endif
}

void sys_putchar(char c){
#ifdef CONFIG_STARRYSKY_C1
    REG_UART_DATA = c;
#elif CONFIG_STARRYSKY_L3
    uint8_t val;
    do
    {
        val = UART_REG_LS;
    } while ((val & 0x20) == 0);
    UART_REG_TH = c;
#endif
}

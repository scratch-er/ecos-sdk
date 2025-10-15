#include "timer.h"
#include "stdio.h"
#include "generated/autoconf.h"

void delay_ms(uint32_t val){
    REG_TIM0_CONFIG = (uint32_t)0x0000;
    for (uint32_t i = 1; i <= val; ++i)
    {
        REG_TIM0_DATA = (uint32_t)(CONFIG_CPU_FREQ_MHZ * 1000 - 1);
        REG_TIM0_CONFIG = (uint32_t)0x0001; // irq disable, count down, continuous mode, timer enable
        while (REG_TIM0_DATA == 0)
            ;
        REG_TIM0_CONFIG = (uint32_t)0x0000;
    }
}
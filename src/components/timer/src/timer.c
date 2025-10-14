#include "timer.h"
#include "generated/autoconf.h"

void delay_ms(uint32_t val){
    // 1ms = 50MHz /
    REG_TIM0_CONFIG = (uint32_t)0x0000;
    REG_TIM0_DATA = (uint32_t)(CONFIG_CPU_FREQ_MHZ * 1000 - 1);
    for (int i = 1; i <= val; ++i)
    {
        REG_TIM0_CONFIG = (uint32_t)0x0001; // irq disable, count down, continuous mode, timer enable
        while (REG_TIM0_DATA == 0)
            ;
        REG_TIM0_CONFIG = (uint32_t)0x0000;
    }
}
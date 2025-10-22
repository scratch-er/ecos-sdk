#include "timer.h"
#include "stdio.h"
#include "generated/autoconf.h"

void delay_us(uint32_t val){
    REG_TIM0_CONFIG = (uint32_t)0x0100;
    REG_TIM0_DATA = (uint32_t)(CONFIG_CPU_FREQ_MHZ * val - 1);
    REG_TIM0_CONFIG = (uint32_t)0x0101; // irq disable, count down, continuous mode, timer enable
    while(REG_TIM0_DATA != 0)
        ;
}

void delay_ms(uint32_t val){
    delay_us(val * 1000);
}

void delay_s(uint32_t val){
    delay_ms(val * 1000);
}

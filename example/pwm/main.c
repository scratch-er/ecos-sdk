#include "main.h"

void main(void){
    
    sys_uart_init();
    printf("PWM test\n");

    pwm_config_t pwm_config = {
        .pscr = 72 - 1,
        .cmp = 1000 - 1,
    };
    pwm_init(&pwm_config);

    while(1){
        for(uint32_t i = 0; i < 990; i+=5){
            pwm_set_compare(PWM_CH0, i);
            delay_ms(5);
        }
        for(uint32_t i = 990; i > 0; i-=5){
            pwm_set_compare(PWM_CH0, i);
            delay_ms(5);
        }
    }



}
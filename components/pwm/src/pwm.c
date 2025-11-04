#include "pwm.h"
#include "board.h"

void pwm_init(pwm_config_t* config){
    REG_CUST_PWM_PSCR = config->pscr;
    REG_CUST_PWM_CMP = config->cmp;
    REG_CUST_PWM_CTRL = 3;
}

void pwm_set_compare(pwm_channel_t ch, uint32_t cmp){
    switch(ch){
        case PWM_CH0:
            REG_CUST_PWM_CR0 = cmp;
            break;
        case PWM_CH1:
            REG_CUST_PWM_CR1 = cmp;
            break;
        case PWM_CH2:
            REG_CUST_PWM_CR2 = cmp;
            break;
        case PWM_CH3:
            REG_CUST_PWM_CR3 = cmp;
            break;
    }
}


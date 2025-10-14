#include "gpio.h"

static void gpio_set_output(uint32_t io_num){
    REG_GPIO_ENB &= ~(0x01 << io_num);
}

static void gpio_set_input(uint32_t io_num){
    REG_GPIO_ENB |= (0x01 << io_num);
}

void gpio_config(const gpio_config_t* config)
{
    if (config == NULL) {
        return;
    }
    
    uint32_t gpio_pin_mask = config->pin_bit_mask;
    uint32_t io_num = 0;
    
    while (io_num < 16){
        if ((gpio_pin_mask >> io_num) & 0x01){
            if (config->mode == GPIO_MODE_INPUT){
                printf("gpio %d set as input\n", io_num);
                gpio_set_input(io_num);
                printf("REG_GPIO_ENB: 0x%x\n", REG_GPIO_ENB);
            } else {
                printf("gpio %d set as output\n", io_num);
                gpio_set_output(io_num);
                printf("REG_GPIO_ENB: 0x%x\n", REG_GPIO_ENB);
            }
        }
        io_num++;
    }
}

void gpio_set_level(gpio_num_t gpio_num, gpio_level_t level){
    if (level == GPIO_LEVEL_HIGH){
        REG_GPIO_DATA |= (0x01 << gpio_num);
    }
    else{
        REG_GPIO_DATA &= ~(0x01 << gpio_num);
    }
}

int32_t gpio_get_level(gpio_num_t gpio_num){
    return (REG_GPIO_DATA >> gpio_num) & 0x01;
}
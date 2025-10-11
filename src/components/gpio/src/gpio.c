#include "gpio.h"

static void gpio_set_output(uint32_t io_num)
{
    reg_gpio_enb |= (0x01 << io_num);
}

static void gpio_set_input(uint32_t io_num)
{
    reg_gpio_enb &= ~(0x01 << io_num);
}

void gpio_config(const gpio_config_t* config)
{
    uint64_t gpio_pin_mask = config->pin_bit_mask;
    uint32_t io_num = 0;
    do{
        if ((gpio_pin_mask >> io_num) & 0x01)
        {
            if (config->mode == GPIO_MODE_INPUT)
            {
                gpio_set_input(io_num);
            }
            else
            {
                gpio_set_output(io_num);
            }
        }
    }
}

void gpio_set_level(gpio_num_t gpio_num, gpio_level_t level){
    if (level == GPIO_LEVEL_HIGH){
        reg_gpio_out |= (0x01 << gpio_num);
    }
    else{
        reg_gpio_out &= ~(0x01 << gpio_num);
    }
}

int32_t gpio_get_level(gpio_num_t gpio_num){
    return (reg_gpio_in >> gpio_num) & 0x01;
}
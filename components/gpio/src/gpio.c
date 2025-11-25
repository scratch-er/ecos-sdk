#include <stddef.h>
#include "gpio.h"
#include "board.h"
#include "generated/autoconf.h"

static void gpio_set_output(uint32_t io_num){
#ifdef CONFIG_GPIO_IP_ID == 0
    REG_GPIO_DDR &= ~(0x01 << io_num);
#elif CONFIG_GPIO_IP_ID == 1

#endif
}

static void gpio_set_input(uint32_t io_num){
#ifdef CONFIG_GPIO_IP_ID == 0
    REG_GPIO_DDR |= (0x01 << io_num);
#elif CONFIG_GPIO_IP_ID == 1

#endif
}

void gpio_config(const gpio_config_t* config)
{
    if (config == NULL) {
        return;
    }
    
    uint64_t gpio_pin_mask = config->pin_bit_mask;
    uint32_t io_num = 0;
    
    while (io_num < 64){
        if ((gpio_pin_mask >> io_num) & 0x01){
            if (config->mode == GPIO_MODE_INPUT){
                gpio_set_input(io_num);
            } else {
                gpio_set_output(io_num);
            }
        }
        io_num++;
    }
}

void gpio_set_level(gpio_num_t gpio_num, gpio_level_t level){
#ifdef CONFIG_GPIO_IP_ID == 0
    if (level == GPIO_LEVEL_HIGH){
        REG_GPIO_DR |= ((uint32_t)0x01 << gpio_num);
    }
    else{
        REG_GPIO_DR &= ~((uint32_t)0x01 << gpio_num);
    }
#elif CONFIG_GPIO_IP_ID == 1

#endif
}

int32_t gpio_get_level(gpio_num_t gpio_num){
#ifdef CONFIG_GPIO_IP_ID == 0
    return (REG_GPIO_DR >> gpio_num) & 0x01;
#elif CONFIG_GPIO_IP_ID == 1
    return 0;
#endif
}
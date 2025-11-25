#include <stddef.h>
#include "gpio.h"
#include "board.h"
#include "generated/autoconf.h"

static void gpio_set_output(uint32_t io_num){
#if CONFIG_GPIO_IP_ID == 0
    REG_GPIO_0_DDR &= ~(0x01 << io_num);
#elif CONFIG_GPIO_IP_ID == 1
    uint8_t io_group = io_num / 32;
    uint8_t io_offset = io_num % 32;
    switch (io_group){
        case 0:
            REG_GPIO_0_PADDIR = REG_GPIO_0_PADDIR | (0x01 << io_offset);
            break;
#ifdef GPIO_GROUP_1
        case 1:
            REG_GPIO_1_PADDIR = REG_GPIO_1_PADDIR | (0x01 << io_offset);
            break;
#endif
        default:
            break;
    }
#endif
}

static void gpio_set_input(uint32_t io_num){
#if CONFIG_GPIO_IP_ID == 0
    REG_GPIO_0_DDR |= (0x01 << io_num);
#elif CONFIG_GPIO_IP_ID == 1
    uint8_t io_group = io_num / 32;
    uint8_t io_offset = io_num % 32;
    switch (io_group){
        case 0:
            REG_GPIO_0_PADDIR = REG_GPIO_0_PADDIR & ~(0x01 << io_offset);
            break;
#ifdef GPIO_GROUP_1
        case 1:
            REG_GPIO_1_PADDIR = REG_GPIO_1_PADDIR & ~(0x01 << io_offset);
            break;
#endif
        default:
            break;
    }
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
    uint8_t io_group = gpio_num / 32;
    uint8_t io_offset = gpio_num % 32;
#if CONFIG_GPIO_IP_ID == 0
    if (level == GPIO_LEVEL_HIGH){
        REG_GPIO_0_DR |= ((uint32_t)0x01 << gpio_num);
    }
    else{
        REG_GPIO_0_DR &= ~((uint32_t)0x01 << gpio_num);
    }
#elif CONFIG_GPIO_IP_ID == 1
    switch (io_group){
        case 0:
            if (level == GPIO_LEVEL_HIGH){
                REG_GPIO_0_PADOUT |= ((uint32_t)0x01 << io_offset);
            }
            else{
                REG_GPIO_0_PADOUT &= ~((uint32_t)0x01 << io_offset);
            }
            break;
#ifdef GPIO_GROUP_1
        case 1:
            if (level == GPIO_LEVEL_HIGH){
                REG_GPIO_1_PADOUT |= ((uint32_t)0x01 << io_offset);
            }
            else{
                REG_GPIO_1_PADOUT &= ~((uint32_t)0x01 << io_offset);
            }
            break;
#endif
        default:
            break;
    }
#endif
}

int32_t gpio_get_level(gpio_num_t gpio_num){
    uint8_t io_group = gpio_num / 32;
    uint8_t io_offset = gpio_num % 32;
#if CONFIG_GPIO_IP_ID == 0
    return (REG_GPIO_0_DR >> gpio_num) & 0x01;
#elif CONFIG_GPIO_IP_ID == 1
    switch (io_group){
        case 0:
            return (REG_GPIO_0_PADIN >> io_offset) & 0x01;
            break;
#ifdef GPIO_GROUP_1
        case 1:
            return (REG_GPIO_1_PADIN >> io_offset) & 0x01;
            break;
#endif
        default:
            break;
    }
    return 0;
#endif
}
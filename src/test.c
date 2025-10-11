#include "gpio.h"

void main(void){
    gpio_config_t config = {
        .pin_bit_mask = (1ULL << GPIO_NUM_2),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&config);
    gpio_set_level(GPIO_NUM_2, GPIO_LEVEL_HIGH);
}
#include "main.h"

void main(void){
    // 配置 GPIO
    gpio_config_t config = {
        .pin_bit_mask = (1ULL << GPIO_NUM_2),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&config);
    gpio_set_level(GPIO_NUM_2, GPIO_LEVEL_HIGH);
    
    // 测试 printf 函数
    printf("Hello, World!\n");
    printf("Testing printf function:\n");
    printf("Character: %c\n", 'A');
    printf("String: %s\n", "Embedded System");
    printf("Decimal: %d\n", 42);
    printf("Negative: %d\n", -123);
    printf("Unsigned: %u\n", 3000000000U);
    printf("Hex lowercase: %x\n", 255);
    printf("Hex uppercase: %X\n", 255);
    printf("Pointer: %p\n", (void*)0x12345678);
    printf("Multiple formats: %s has %d items, value: 0x%X\n", "Array", 10, 0xABCD);
}
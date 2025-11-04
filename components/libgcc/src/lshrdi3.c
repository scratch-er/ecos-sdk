#include <stdint.h>

// 64位逻辑右移函数实现
uint64_t __lshrdi3(uint64_t a, int b) {
    if (b == 0) return a;
    if (b >= 64) return 0;
    
    return a >> b;
}
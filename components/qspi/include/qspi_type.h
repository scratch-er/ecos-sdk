#ifndef __QSPI_TYPE_H__
#define __QSPI_TYPE_H__

#include <stdint.h>

typedef struct {
    uint32_t clkdiv; // QSPI时钟分频值
} qspi_config_t;

#endif
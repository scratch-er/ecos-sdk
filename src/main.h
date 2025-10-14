// System Headers
#include "string.h"
#include "stdio.h"
#include "libgcc.h"

// Component Headers
#include "gpio.h"
#include "qspi.h"

// Device Headers
#include "st7735.h"

// System Configuration
#include "generated/autoconf.h"

#define PSRAM_SCKL_FREQ_MHZ (CONFIG_CPU_FREQ_MHZ / CONFIG_PSRAM_NUM)
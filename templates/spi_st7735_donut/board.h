#ifndef __STARRYSKY_C1_H__
#define __STARRYSKY_C1_H__

/* ========== GPIO 寄存器组 ========== */
#define REG_GPIO_DR           (*(volatile uint32_t*)0x03000000)  // GPIO数据寄存器
#define REG_GPIO_DDR          (*(volatile uint32_t*)0x03000004)  // GPIO数据方向寄存器
#define REG_GPIO_PUB          (*(volatile uint32_t*)0x03000008)  // GPIO上拉使能寄存器
#define REG_GPIO_PDB          (*(volatile uint32_t*)0x0300000c)  // GPIO下拉使能寄存器

#endif

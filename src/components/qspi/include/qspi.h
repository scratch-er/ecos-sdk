#ifndef __QSPI_H__
#define __QSPI_H__
#include "qspi_type.h"
/* ========== QSPI 接口寄存器 ========== */
#define REG_CUST_QSPI_STATUS  (*(volatile uint32_t*)0x03007000)  // QSPI状态寄存器
#define REG_CUST_QSPI_CLKDIV  (*(volatile uint32_t*)0x03007004)  // QSPI时钟分频寄存器
#define REG_CUST_QSPI_CMD     (*(volatile uint32_t*)0x03007008)  // QSPI命令寄存器
#define REG_CUST_QSPI_ADR     (*(volatile uint32_t*)0x0300700c)  // QSPI地址寄存器
#define REG_CUST_QSPI_LEN     (*(volatile uint32_t*)0x03007010)  // QSPI长度寄存器
#define REG_CUST_QSPI_DUM     (*(volatile uint32_t*)0x03007014)  // QSPI虚拟周期寄存器
#define REG_CUST_QSPI_TXFIFO  (*(volatile uint32_t*)0x03007018)  // QSPI发送FIFO寄存器
#define REG_CUST_QSPI_RXFIFO  (*(volatile uint32_t*)0x03007020)  // QSPI接收FIFO寄存器
#define REG_CUST_QSPI_INTCFG  (*(volatile uint32_t*)0x03007024)  // QSPI中断配置寄存器
#define REG_CUST_QSPI_INTSTA  (*(volatile uint32_t*)0x03007028)  // QSPI中断状态寄存器

void qspi_init(qspi_config_t *config);
void qspi_write_8(uint8_t data);
void qspi_write_16(uint16_t data);
void qspi_write_32(uint32_t data);
void qspi_write_32x2(uint32_t data1, uint32_t data2);
void qspi_write_32x8(uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4, uint32_t data5, uint32_t data6, uint32_t data7, uint32_t data8);
void qspi_write_32x16(uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4, uint32_t data5, uint32_t data6, uint32_t data7, uint32_t data8,
     uint32_t data9, uint32_t data10, uint32_t data11, uint32_t data12, uint32_t data13, uint32_t data14, uint32_t data15, uint32_t data16);
void qspi_write_32x32(uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4, uint32_t data5, uint32_t data6, uint32_t data7, uint32_t data8,
     uint32_t data9, uint32_t data10, uint32_t data11, uint32_t data12, uint32_t data13, uint32_t data14, uint32_t data15, uint32_t data16,
     uint32_t data17, uint32_t data18, uint32_t data19, uint32_t data20, uint32_t data21, uint32_t data22, uint32_t data23, uint32_t data24,
     uint32_t data25, uint32_t data26, uint32_t data27, uint32_t data28, uint32_t data29, uint32_t data30, uint32_t data31, uint32_t data32);


#endif
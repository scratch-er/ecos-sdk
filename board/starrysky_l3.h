#ifndef __STARRYSKY_L3_H__
#define __STARRYSKY_L3_H__

/* ========== SYS_UART 寄存器组 ======== */
#define UART_REG_RB *((volatile uint8_t *)0x10000000)
#define UART_REG_TH *((volatile uint8_t *)0x10000000)
#define UART_REG_IE *((volatile uint8_t *)0x10000001)
#define UART_REG_II *((volatile uint8_t *)0x10000002)
#define UART_REG_FC *((volatile uint8_t *)0x10000002)
#define UART_REG_LC *((volatile uint8_t *)0x10000003)
#define UART_REG_MC *((volatile uint8_t *)0x10000004)
#define UART_REG_LS *((volatile uint8_t *)0x10000005)
#define UART_REG_MS *((volatile uint8_t *)0x10000006)

/* ========== QSPI 接口寄存器 ========== */
#define REG_CUST_QSPI_STATUS  *((volatile uint32_t *)(0x10010000))
#define REG_CUST_QSPI_CLKDIV  *((volatile uint32_t *)(0x10010004))
#define REG_CUST_QSPI_CMD     *((volatile uint32_t *)(0x10010008))
#define REG_CUST_QSPI_ADR     *((volatile uint32_t *)(0x1001000C))
#define REG_CUST_QSPI_LEN     *((volatile uint32_t *)(0x10010010))
#define REG_CUST_QSPI_DUM     *((volatile uint32_t *)(0x10010014))
#define REG_CUST_QSPI_TXFIFO  *((volatile uint32_t *)(0x10010018))
#define REG_CUST_QSPI_RXFIFO  *((volatile uint32_t *)(0x10010020))
#define REG_CUST_QSPI_INTCFG  *((volatile uint32_t *)(0x10010024))
#define REG_CUST_QSPI_INTSTA  *((volatile uint32_t *)(0x10010028))

/* ========== I2C 接口寄存器 ========== */
#define REG_CUST_I2C_CTRL  *((volatile uint8_t *)0x1000D000)
#define REG_CUST_I2C_PSCR  *((volatile uint8_t *)0x1000D004)
#define REG_CUST_I2C_TXR   *((volatile uint8_t *)0x1000D008)
#define REG_CUST_I2C_RXR   *((volatile uint8_t *)0x1000D00C)
#define REG_CUST_I2C_CMD   *((volatile uint8_t *)0x1000D010)
#define REG_CUST_I2C_SR    *((volatile uint8_t *)0x1000D014)
#endif

#ifndef __STARRYSKY_C1_H__
#define __STARRYSKY_C1_H__

/* ========== GPIO 寄存器组 ========== */
#define REG_GPIO_0_DR         (*(volatile uint32_t*)0x03000000)  // GPIO数据寄存器
#define REG_GPIO_0_DDR        (*(volatile uint32_t*)0x03000004)  // GPIO数据方向寄存器
#define REG_GPIO_0_PUB        (*(volatile uint32_t*)0x03000008)  // GPIO上拉使能寄存器
#define REG_GPIO_0_PDB        (*(volatile uint32_t*)0x0300000c)  // GPIO下拉使能寄存器

/* ========== HP_UART 寄存器组 ======= */
#define REG_CUST_UART_LCR     (*(volatile uint32_t*)0x03003000)  // UART线路控制寄存器
#define REG_CUST_UART_DIV     (*(volatile uint32_t*)0x03003004)  // UART分频寄存器
#define REG_CUST_UART_TRX     (*(volatile uint32_t*)0x03003008)  // UART收发寄存器
#define REG_CUST_UART_FCR     (*(volatile uint32_t*)0x0300300c)  // UART FIFO控制寄存器
#define REG_CUST_UART_LSR     (*(volatile uint32_t*)0x03003010)  // UART线路状态寄存器

/* ========== I2C 接口寄存器 ========== */
#define REG_CUST_I2C_CTRL     (*(volatile uint32_t*)0x03006000)  // I2C控制寄存器
#define REG_CUST_I2C_PSCR     (*(volatile uint32_t*)0x03006004)  // I2C预分频寄存器
#define REG_CUST_I2C_TXR      (*(volatile uint32_t*)0x03006008)  // I2C发送寄存器
#define REG_CUST_I2C_RXR      (*(volatile uint32_t*)0x0300600c)  // I2C接收寄存器
#define REG_CUST_I2C_CMD      (*(volatile uint32_t*)0x03006010)  // I2C命令寄存器
#define REG_CUST_I2C_SR       (*(volatile uint32_t*)0x03006014)  // I2C状态寄存器

/* ========== PWM 寄存器组 ========== */
#define REG_CUST_PWM_CTRL     (*(volatile uint32_t*)0x03004000)  // PWM控制寄存器
#define REG_CUST_PWM_PSCR     (*(volatile uint32_t*)0x03004004)  // PWM预分频寄存器
#define REG_CUST_PWM_CNT      (*(volatile uint32_t*)0x03004008)  // PWM计数寄存器
#define REG_CUST_PWM_CMP      (*(volatile uint32_t*)0x0300400c)  // PWM比较寄存器
#define REG_CUST_PWM_CR0      (*(volatile uint32_t*)0x03004010)  // PWM通道0比较寄存器
#define REG_CUST_PWM_CR1      (*(volatile uint32_t*)0x03004014)  // PWM通道1比较寄存器
#define REG_CUST_PWM_CR2      (*(volatile uint32_t*)0x03004018)  // PWM通道2比较寄存器
#define REG_CUST_PWM_CR3      (*(volatile uint32_t*)0x0300401c)  // PWM通道3比较寄存器
#define REG_CUST_PWM_STAT     (*(volatile uint32_t*)0x03004020)  // PWM状态寄存器

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

/* ========== SYS_UART 接口寄存器 ====== */
#define REG_UART_0_CLKDIV       (*(volatile uint32_t*)0x03000010)  // UART时钟分频寄存器
#define REG_UART_0_DATA         (*(volatile uint32_t*)0x03000014)  // UART数据寄存器

/* ========== 定时器 寄存器组 =========== */
#define REG_TIM0_CONFIG       (*(volatile uint32_t*)0x0300005c)  // 定时器0配置寄存器
#define REG_TIM0_VALUE        (*(volatile uint32_t*)0x03000060)  // 定时器0计数值寄存器
#define REG_TIM0_DATA         (*(volatile uint32_t*)0x03000064)  // 定时器0数据寄存器

#define REG_TIM1_CONFIG       (*(volatile uint32_t*)0x03000068)  // 定时器1配置寄存器
#define REG_TIM1_VALUE        (*(volatile uint32_t*)0x0300006c)  // 定时器1计数值寄存器
#define REG_TIM1_DATA         (*(volatile uint32_t*)0x03000070)  // 定时器1数据寄存器

#endif

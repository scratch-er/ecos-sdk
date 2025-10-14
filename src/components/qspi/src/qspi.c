#include "qspi.h"
#include "stdio.h"

void qspi_init(qspi_config_t *config){
    REG_CUST_QSPI_STATUS = (uint32_t)0b10000;
    REG_CUST_QSPI_STATUS = (uint32_t)0b00000;
    REG_CUST_QSPI_INTCFG = (uint32_t)0b00000;
    REG_CUST_QSPI_DUM = (uint32_t)0;
    REG_CUST_QSPI_CLKDIV = config->clkdiv; // sck = apb_clk/2(div+1)
    printf("qspi_status: %x\n", REG_CUST_QSPI_STATUS);
    printf("qspi_intcfg: %x\n", REG_CUST_QSPI_INTCFG);
    printf("qspi_dum: %x\n", REG_CUST_QSPI_DUM);
    printf("qspi_clkdiv: %x\n", REG_CUST_QSPI_CLKDIV);
}

void qspi_write_8(uint8_t data){
    uint32_t wdat = ((uint32_t)data) << 24;
    REG_CUST_QSPI_LEN = 0x80000;
    REG_CUST_QSPI_TXFIFO = wdat;
    REG_CUST_QSPI_STATUS = 258;
    while ((REG_CUST_QSPI_STATUS & 0xFFFFFFFF) != 1)
        ;
}

void qspi_write_16(uint16_t data){
    uint32_t wdat = ((uint32_t)data) << 16;
    REG_CUST_QSPI_LEN = 0x100000;
    REG_CUST_QSPI_TXFIFO = wdat;
    REG_CUST_QSPI_STATUS = 258;
    while ((REG_CUST_QSPI_STATUS & 0xFFFFFFFF) != 1)
        ;
}

void qspi_write_32(uint32_t data){
    REG_CUST_QSPI_LEN = 0x200000;
    REG_CUST_QSPI_TXFIFO = data;
    REG_CUST_QSPI_STATUS = 258;
    while ((REG_CUST_QSPI_STATUS & 0xFFFFFFFF) != 1)
        ;
}

void qspi_write_32x2(uint32_t data1, uint32_t data2){
    REG_CUST_QSPI_LEN = 0x400000;
    REG_CUST_QSPI_TXFIFO = data1;
    REG_CUST_QSPI_TXFIFO = data2;
    REG_CUST_QSPI_STATUS = 258;
    while ((REG_CUST_QSPI_STATUS & 0xFFFFFFFF) != 1)
        ;
}

void qspi_write_32x8(uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4, uint32_t data5, uint32_t data6, uint32_t data7, uint32_t data8){
    REG_CUST_QSPI_LEN = 0x1000000;
    REG_CUST_QSPI_TXFIFO = data1;
    REG_CUST_QSPI_TXFIFO = data2;
    REG_CUST_QSPI_TXFIFO = data3;
    REG_CUST_QSPI_TXFIFO = data4;
    REG_CUST_QSPI_TXFIFO = data5;
    REG_CUST_QSPI_TXFIFO = data6;
    REG_CUST_QSPI_TXFIFO = data7;
    REG_CUST_QSPI_TXFIFO = data8;
    REG_CUST_QSPI_STATUS = 258;
    while ((REG_CUST_QSPI_STATUS & 0xFFFFFFFF) != 1)
        ;
}

void qspi_write_32x16(uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4, uint32_t data5, uint32_t data6, uint32_t data7, uint32_t data8,
     uint32_t data9, uint32_t data10, uint32_t data11, uint32_t data12, uint32_t data13, uint32_t data14, uint32_t data15, uint32_t data16){
    REG_CUST_QSPI_LEN = 0x2000000;
    REG_CUST_QSPI_TXFIFO = data1;
    REG_CUST_QSPI_TXFIFO = data2;
    REG_CUST_QSPI_TXFIFO = data3;
    REG_CUST_QSPI_TXFIFO = data4;
    REG_CUST_QSPI_TXFIFO = data5;
    REG_CUST_QSPI_TXFIFO = data6;
    REG_CUST_QSPI_TXFIFO = data7;
    REG_CUST_QSPI_TXFIFO = data8;
    REG_CUST_QSPI_TXFIFO = data9;
    REG_CUST_QSPI_TXFIFO = data10;
    REG_CUST_QSPI_TXFIFO = data11;
    REG_CUST_QSPI_TXFIFO = data12;
    REG_CUST_QSPI_TXFIFO = data13;
    REG_CUST_QSPI_TXFIFO = data14;
    REG_CUST_QSPI_TXFIFO = data15;
    REG_CUST_QSPI_TXFIFO = data16;
    REG_CUST_QSPI_STATUS = 258;
    while ((REG_CUST_QSPI_STATUS & 0xFFFFFFFF) != 1)
        ;
}

void qspi_write_32x32(uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4, uint32_t data5, uint32_t data6, uint32_t data7, uint32_t data8,
     uint32_t data9, uint32_t data10, uint32_t data11, uint32_t data12, uint32_t data13, uint32_t data14, uint32_t data15, uint32_t data16,
     uint32_t data17, uint32_t data18, uint32_t data19, uint32_t data20, uint32_t data21, uint32_t data22, uint32_t data23, uint32_t data24,
     uint32_t data25, uint32_t data26, uint32_t data27, uint32_t data28, uint32_t data29, uint32_t data30, uint32_t data31, uint32_t data32){
        
    REG_CUST_QSPI_LEN = 0x4000000;
    REG_CUST_QSPI_TXFIFO = data1;
    REG_CUST_QSPI_TXFIFO = data2;
    REG_CUST_QSPI_TXFIFO = data3;
    REG_CUST_QSPI_TXFIFO = data4;
    REG_CUST_QSPI_TXFIFO = data5;
    REG_CUST_QSPI_TXFIFO = data6;
    REG_CUST_QSPI_TXFIFO = data7;
    REG_CUST_QSPI_TXFIFO = data8;
    REG_CUST_QSPI_TXFIFO = data9;
    REG_CUST_QSPI_TXFIFO = data10;
    REG_CUST_QSPI_TXFIFO = data11;
    REG_CUST_QSPI_TXFIFO = data12;
    REG_CUST_QSPI_TXFIFO = data13;
    REG_CUST_QSPI_TXFIFO = data14;
    REG_CUST_QSPI_TXFIFO = data15;
    REG_CUST_QSPI_TXFIFO = data16;
    REG_CUST_QSPI_TXFIFO = data17;
    REG_CUST_QSPI_TXFIFO = data18;
    REG_CUST_QSPI_TXFIFO = data19;
    REG_CUST_QSPI_TXFIFO = data20;
    REG_CUST_QSPI_TXFIFO = data21;
    REG_CUST_QSPI_TXFIFO = data22;
    REG_CUST_QSPI_TXFIFO = data23;
    REG_CUST_QSPI_TXFIFO = data24;
    REG_CUST_QSPI_TXFIFO = data25;
    REG_CUST_QSPI_TXFIFO = data26;
    REG_CUST_QSPI_TXFIFO = data27;
    REG_CUST_QSPI_TXFIFO = data28;
    REG_CUST_QSPI_TXFIFO = data29;
    REG_CUST_QSPI_TXFIFO = data30;
    REG_CUST_QSPI_TXFIFO = data31;
    REG_CUST_QSPI_TXFIFO = data32;
    REG_CUST_QSPI_STATUS = 258;
    printf("qspi_status: %x\n", REG_CUST_QSPI_STATUS);
    while ((REG_CUST_QSPI_STATUS & 0xFFFFFFFF) != 1)
        ;
    printf("qspi_status: %x\n", REG_CUST_QSPI_STATUS);
}

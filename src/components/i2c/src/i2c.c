#include "i2c.h"
#include "stdio.h"

void i2c_init(i2c_config_t* config){
    REG_CUST_I2C_CTRL = (uint32_t)0;
    REG_CUST_I2C_PSCR = config->pscr;
    REG_CUST_I2C_CTRL = (uint32_t)0b10000000;
}

static uint32_t i2c_get_ack(){
    while((REG_CUST_I2C_SR & I2C_STATUS_TIP) == 0);
    while((REG_CUST_I2C_SR & I2C_STATUS_TIP) != 0);
    return !(REG_CUST_I2C_SR & I2C_STATUS_RXACK);
}

static uint32_t i2c_busy(){
    return ((REG_CUST_I2C_SR & I2C_STATUS_BUSY) == I2C_STATUS_BUSY);
}
static void i2c_start_write(uint8_t slave_addr){
    REG_CUST_I2C_TXR = slave_addr;
    REG_CUST_I2C_CMD = I2C_START_WRITE;
    if(!i2c_get_ack()){
        printf("I2C: start write no ack\n");
    }
}

static void i2c_start_read(uint8_t slave_addr){
    REG_CUST_I2C_TXR = slave_addr;
    REG_CUST_I2C_CMD = I2C_START_READ;
    if(!i2c_get_ack()){
        printf("I2C: start read no ack\n");
    }
}

static void i2c_stop(){
    REG_CUST_I2C_CMD = I2C_STOP;
    while(i2c_busy());
}

static void i2c_write_byte(uint8_t byte){
    REG_CUST_I2C_TXR = byte;
    REG_CUST_I2C_CMD = I2C_WRITE;
    if(!i2c_get_ack()){
        printf("I2C: write byte no ack\n");
    }
}

static uint32_t i2c_read_byte(i2c_cmd_t cmd){
    REG_CUST_I2C_CMD = cmd;
    if(!i2c_get_ack()){
        printf("I2C: read byte no ack\n");
    }
    return REG_CUST_I2C_RXR;
}

void i2c_write_nbyte(uint8_t slave_addr, uint16_t reg_addr, i2c_reg_addr_len_t reg_addr_len,uint8_t* data, uint32_t len){
    i2c_start_write(slave_addr);
    if(reg_addr_len == I2C_REG_8){
        i2c_write_byte((uint8_t)(reg_addr & 0xFF));
    }else{
        i2c_write_byte((uint8_t)(reg_addr >> 8) & 0xFF);
        i2c_write_byte((uint8_t)(reg_addr & 0xFF));
    }
    for(uint32_t i = 0; i < len; i++){
        i2c_write_byte(data[i]);
    }
    i2c_stop();
}

void i2c_read_nbyte(uint8_t slave_addr, uint16_t reg_addr, i2c_reg_addr_len_t reg_addr_len,uint8_t* data, uint32_t len){
    i2c_start_write(slave_addr);
    if(reg_addr_len == I2C_REG_8){
        i2c_write_byte((uint8_t)(reg_addr & 0xFF));
    }else{
        i2c_write_byte((uint8_t)(reg_addr >> 8) & 0xFF);
        i2c_write_byte((uint8_t)(reg_addr & 0xFF));
    }
    i2c_stop();

    i2c_start_read(slave_addr + 1);
    for(uint32_t i = 0; i < len; i++){
        data[i] = (uint8_t)i2c_read_byte(i == len - 1 ? I2C_STOP_READ : I2C_READ);
    }
    i2c_stop();
}

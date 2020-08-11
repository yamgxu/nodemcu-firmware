#include "stdint.h"
#include "math.h"

#define MPU6050
uint16_t i2c_setup(unsigned id, uint8_t sda, uint8_t scl) ;
uint16_t IICreadBytes(uint16_t ads_addr, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t  IICreadByte(uint16_t ads_addr, uint8_t reg,uint8_t *data);
uint8_t  IICreadByteOne(uint16_t ads_addr, uint8_t reg);
uint16_t IICwriteBytes(uint16_t ads_addr, uint8_t reg, uint8_t length, uint8_t *data) ;
unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data);
uint16_t IICwriteBit(uint8_t slave_addr, uint8_t reg_addr, uint8_t bitNum, uint8_t data);
uint16_t IICwriteBits(uint8_t slave_addr, uint8_t reg_addr, uint8_t bitStart, uint8_t length, uint8_t data);


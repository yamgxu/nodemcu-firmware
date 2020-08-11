#include "I2C.h"
#include "mpu6050.h"
#include <stdint.h>
#include "../platform/platform.h"
#include "mpu6050.h"
uint16_t i2c_setup(unsigned id, uint8_t sda, uint8_t scl) {
    return   platform_i2c_setup( id, sda, scl,  PLATFORM_I2C_SPEED_SLOW );
}


/**************************实现函数********************************************
*函数原型:		u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data)
*功　　能:	    读取指定设备 指定寄存器的 length个值
输入	dev  目标设备地址
		reg	  寄存器地址
		length 要读的字节数
		*data  读出的数据将要存放的指针
返回   读出来的字节数量
*******************************************************************************/
uint16_t IICreadBytes(uint16_t ads_addr, uint8_t reg, uint8_t length, uint8_t *data) {
    MPU6050_DEBUG("IICreadBytes:  ads_addr(%04x), reg(%04x), length(%d)\n",ads_addr, reg, length);
    platform_i2c_send_start(0);
    platform_i2c_send_address(0, ads_addr, PLATFORM_I2C_DIRECTION_TRANSMITTER);
    platform_i2c_send_byte(0, reg);
    platform_i2c_send_stop(0);
    platform_i2c_send_start(0);
    platform_i2c_send_address(0, ads_addr, PLATFORM_I2C_DIRECTION_RECEIVER);
    int i;
    for (i = 0; i < length; i++) {
        if ((data[i] = platform_i2c_recv_byte(0, i < length - 1)) == -1)
            break;
    }
    platform_i2c_send_stop(0);
}
/**************************实现函数********************************************
*函数原型:		u8 IICreadByte(u8 dev, u8 reg, u8 *data)
*功　　能:	    读取指定设备 指定寄存器的一个值
输入	dev  目标设备地址
		reg	   寄存器地址
		*data  读出的数据将要存放的地址
返回   1
*******************************************************************************/
uint8_t IICreadByte(uint16_t ads_addr, uint8_t reg,uint8_t *data){
    IICreadBytes(ads_addr, reg,1,data);
    return 1;
}

uint8_t IICreadByteOne(uint16_t ads_addr, uint8_t reg){
    uint8_t data=0;
    IICreadBytes(ads_addr, reg,1,&data);
    return data;
}


/**************************实现函数********************************************
*函数原型:		u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data)
*功　　能:	    将多个字节写入指定设备 指定寄存器
输入	dev  目标设备地址
		reg	  寄存器地址
		length 要写的字节数
		*data  将要写的数据的首地址
返回   返回是否成功
*******************************************************************************/
uint16_t IICwriteBytes(uint16_t ads_addr, uint8_t reg, uint8_t length, uint8_t *data) {
    MPU6050_DEBUG("i2c_write:  ads_addr(%04x), reg(%04x), length(%d)\n",ads_addr, reg, length);
    uint8_t n;
    for (n = 0; n < length; n++) {
        platform_i2c_send_start(0);
        platform_i2c_send_address(0, ads_addr, PLATFORM_I2C_DIRECTION_TRANSMITTER);
        platform_i2c_send_byte(0, reg);
        int i;
        for (i = 0; i < length; i++) {
            if (platform_i2c_send_byte(0, data[i]) == 0)
                break;
        }
        platform_i2c_send_stop(0);
    }
    return 0;
}


/**************************实现函数********************************************
*函数原型:		unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data)
*功　　能:	    写入指定设备 指定寄存器一个字节
输入	dev  目标设备地址
		reg	   寄存器地址
		data  将要写入的字节
返回   1
*******************************************************************************/
unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data){
    return IICwriteBytes(dev, reg, 1, &data);
}
/**************************实现函数********************************************
*函数原型:		u8 IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data)
*功　　能:	    读 修改 写 指定设备 指定寄存器一个字节 中的1个位
输入	dev  目标设备地址
		reg	   寄存器地址
		bitNum  要修改目标字节的bitNum位
		data  为0 时，目标位将被清0 否则将被置位
返回   成功 为1
 		   失败为0
*******************************************************************************/
uint16_t IICwriteBit(uint8_t slave_addr, uint8_t reg_addr, uint8_t bitNum, uint8_t data) {
    uint8_t tmp;
    IICreadBytes(slave_addr, reg_addr, 1, &tmp);
    tmp = (data != 0) ? (tmp | (1 << bitNum)) : (tmp & ~(1 << bitNum));
    return IICwriteBytes(slave_addr, reg_addr, 1, &tmp);
}
/**************************实现函数********************************************
*函数原型:		u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
*功　　能:	    读 修改 写 指定设备 指定寄存器一个字节 中的多个位
输入	dev  目标设备地址
		reg	   寄存器地址
		bitStart  目标字节的起始位
		length   位长度
		data    存放改变目标字节位的值
返回   成功 为1
 		失败为0
*******************************************************************************/
uint16_t IICwriteBits(uint8_t slave_addr, uint8_t reg_addr, uint8_t bitStart, uint8_t length, uint8_t data) {
    uint8_t tmp, dataShift;
    IICreadBytes(slave_addr, reg_addr, 1, &tmp);
    uint8_t mask = (((1 << length) - 1) << (bitStart - length + 1));
    dataShift = data << (bitStart - length + 1);
    tmp &= mask;
    tmp |= dataShift;

    return IICwriteBytes(slave_addr, reg_addr, 1, &tmp);
}


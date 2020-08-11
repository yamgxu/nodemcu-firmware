//
// Created by 77039 on 2020/8/9.
//

#include "sendData.h"

#include "platform.h"
#include <stdint.h>


#define BYTE0(dwTemp) (*(char *)(&dwTemp))

#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))

#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))

#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))


/**

* @brief 控制串口发送1个字符

* @param c:要发送的字符

 * @retval none

 */

void usart_send_char(uint8_t c) {
    platform_uart_send( 0,  ( u8 )c);
}


/*函数功能：根据匿名最新上位机协议写的显示姿态的程序（上位机0512版本）

*具体协议说明请查看上位机软件的帮助说明。

*/

void Data_Send_Status(float Pitch, float Roll, float Yaw) {

    unsigned char i = 0;

    unsigned char _cnt = 0, sum = 0;

    unsigned int _temp;

    u8 data_to_send[50];


    data_to_send[_cnt++] = 0xAA;

    data_to_send[_cnt++] = 0x05;

    data_to_send[_cnt++] = 0xAF;

    data_to_send[_cnt++] =  0x01;
    data_to_send[_cnt++] =  0x00;


    _temp = (int) (Roll * 100);

    data_to_send[_cnt++] = BYTE1(_temp);

    data_to_send[_cnt++] = BYTE0(_temp);

    _temp = 0 - (int) (Pitch * 100);

    data_to_send[_cnt++] = BYTE1(_temp);

    data_to_send[_cnt++] = BYTE0(_temp);

    _temp = (int) (Yaw * 100);

    data_to_send[_cnt++] = BYTE1(_temp);

    data_to_send[_cnt++] = BYTE0(_temp);

    _temp = 0;

    data_to_send[_cnt++] = BYTE3(_temp);

    data_to_send[_cnt++] = BYTE2(_temp);

    data_to_send[_cnt++] = BYTE1(_temp);

    data_to_send[_cnt++] = BYTE0(_temp);


    data_to_send[_cnt++] = 0x00;
    data_to_send[_cnt++] = 0x00;


    data_to_send[4] = _cnt - 5;

    //和校验

    for (i = 0; i < _cnt; i++)
    {
        sum += data_to_send[i];
    }
    data_to_send[_cnt++] = sum;



    //串口发送数据

    for (i = 0; i < _cnt; i++)
    {
        usart_send_char(data_to_send[i]);
    }
}


/*函数功能：根据匿名最新上位机协议写的显示传感器数据（上位机0512版本）

*具体协议说明请查看上位机软件的帮助说明。

*/

void Send_Data(int16_t *Gyro, int16_t *Accel) {

    unsigned char i = 0;

    unsigned char _cnt = 0, sum = 0;

    // unsigned int _temp;

    u8 data_to_send[50];


    data_to_send[_cnt++] = 0xAA;

    data_to_send[_cnt++] = 0x05;

    data_to_send[_cnt++] = 0xAF;

    data_to_send[_cnt++] =  0x02;
    data_to_send[_cnt++] =  0x00;


    data_to_send[_cnt++] = BYTE1(Accel[0]);

    data_to_send[_cnt++] = BYTE0(Accel[0]);

    data_to_send[_cnt++] = BYTE1(Accel[1]);

    data_to_send[_cnt++] = BYTE0(Accel[1]);

    data_to_send[_cnt++] = BYTE1(Accel[2]);

    data_to_send[_cnt++] = BYTE0(Accel[2]);


    data_to_send[_cnt++] = BYTE1(Gyro[0]);

    data_to_send[_cnt++] = BYTE0(Gyro[0]);

    data_to_send[_cnt++] = BYTE1(Gyro[1]);

    data_to_send[_cnt++] = BYTE0(Gyro[1]);

    data_to_send[_cnt++] = BYTE1(Gyro[2]);

    data_to_send[_cnt++] = BYTE0(Gyro[2]);

    data_to_send[_cnt++] = 0;

    data_to_send[_cnt++] = 0;

    data_to_send[_cnt++] = 0;

    data_to_send[_cnt++] = 0;

    data_to_send[_cnt++] = 0;

    data_to_send[_cnt++] = 0;


    data_to_send[4] = _cnt - 5;

    //和校验

    for (i = 0; i < _cnt; i++)
    {
        sum += data_to_send[i];
    }
    data_to_send[_cnt++] = sum;



    //串口发送数据

    for (i = 0; i < _cnt; i++)
    {
        usart_send_char(data_to_send[i]);
    }
}
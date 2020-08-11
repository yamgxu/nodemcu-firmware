//
// Created by 77039 on 2020/8/9.
//

#ifndef NODEMCU_FIRMWARE_SENDDATA_H
#define NODEMCU_FIRMWARE_SENDDATA_H
#include <stdint.h>
void Data_Send_Status(float Pitch, float Roll, float Yaw) ;
void Send_Data(int16_t *Gyro, int16_t *Accel) ;
#endif //NODEMCU_FIRMWARE_SENDDATA_H

#include "module.h"
#include "../quadrotor/imu.h"
#include "../quadrotor/IMUSO3.h"
#include "../quadrotor/filter.h"
#include "../quadrotor/MPU6050.h"
#include "../quadrotor/I2C.h"
#include "../quadrotor/sendData.h"
#include "lauxlib.h"
#include <stdio.h>



static int quadrotor_luaMahonyUpdate(lua_State* L) {
    //float gx = luaL_checknumber(L, 1);
    //float gy = luaL_checknumber(L, 2);
    //float gz = luaL_checknumber(L, 3);
    //float ax = luaL_checknumber(L, 4);
    //float ay = luaL_checknumber(L, 5);
    //float az = luaL_checknumber(L, 6);
    //float mx = luaL_checknumber(L, 7);
    //float my = luaL_checknumber(L, 8);
    //float mz = luaL_checknumber(L, 9);


    //read raw
    //MPU6050AccRead(imu.accADC);
    //MPU6050GyroRead(imu.gyroADC);
    //tutn to physical
   // int16_t gx = (int16_t) luaL_checknumber(L, 1);
   // int16_t gy = (int16_t) luaL_checknumber(L, 2);
   // int16_t gz = (int16_t) luaL_checknumber(L, 3);
   // int16_t ax = (int16_t) luaL_checknumber(L, 4);
   // int16_t ay = (int16_t) luaL_checknumber(L, 5);
   // int16_t az = (int16_t) luaL_checknumber(L, 6);


    IMUSO3Thread();
    //imu校准
    if(imuCaliFlag)
    {
        if(IMU_Calibrate())
        {
            imuCaliFlag=0;
          //  gParamsSaveEEPROMRequset=1;	//请求记录到EEPROM
            imu.caliPass=1;
        }
    }
    int16_t ii = (int16_t) luaL_checknumber(L, 1);
    if(ii>0){
        Data_Send_Status( imu.pitch,imu.roll, imu.yaw);
    }
    if(ii>1){
        Send_Data( imu.gyroADC,imu.accADC);
    }
    lua_pushnumber(L, imu.pitch);
    lua_pushnumber(L, imu.roll);
    lua_pushnumber(L, imu.yaw);
    return 3;

}
static int quadrotor_IMU_Init(lua_State* L) {

    IMU_Init();
    return 1;
}
static int quadrotor_i2c_setup(lua_State* L) {
    unsigned id = luaL_checkinteger( L, 1 );
    unsigned sda = luaL_checkinteger( L, 2 );
    unsigned scl = luaL_checkinteger( L, 3 );

    int16_t i = i2c_setup(id,sda,scl);
    lua_pushnumber(L, i);
    return 1;
}
static int quadrotor_MPU6050_initialize(lua_State* L) {
    MPU6050_initialize();
    return 0;
}
static int quadrotor_MPU6050GyroRead(lua_State* L) {
    int16_t buf[3];
    MPU6050GyroRead(buf);

    lua_pushnumber(L, buf[0]);
    lua_pushnumber(L, buf[1]);
    lua_pushnumber(L, buf[2]);

    return 3;
}
static int quadrotor_MPU6050AccRead(lua_State* L) {
    int16_t buf[3];
    MPU6050AccRead(buf);
    lua_pushnumber(L, buf[0]);
    lua_pushnumber(L, buf[1]);
    lua_pushnumber(L, buf[2]);


        return 3;
}


// Module function map
LROT_BEGIN(quadrotor, NULL, 0)
  LROT_FUNCENTRY( luaMahonyUpdate, quadrotor_luaMahonyUpdate )
  LROT_FUNCENTRY( IMU_Init, quadrotor_IMU_Init )
  LROT_FUNCENTRY( quadrotor_i2c_setup, quadrotor_i2c_setup )
  LROT_FUNCENTRY( quadrotor_MPU6050_initialize, quadrotor_MPU6050_initialize )
  LROT_FUNCENTRY( quadrotor_MPU6050GyroRead, quadrotor_MPU6050GyroRead )
  LROT_FUNCENTRY( quadrotor_MPU6050AccRead, quadrotor_MPU6050AccRead )
LROT_END(quadrotor, NULL, 0)


NODEMCU_MODULE(QUADROTOR, "quadrotor", quadrotor, NULL);

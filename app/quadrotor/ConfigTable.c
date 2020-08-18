/**
* EEPROM Table by samit
**/

#include "ConfigTable.h"
#include "Control.h"
#include "imu.h"
#include "SysConfig.h"


//用来存放EEPROM列表上的存放的参数变量的信息
config_table_t table;				//tobe improved: config mean in const / eeprom.
//请求保存参数到EEPROM的信号量
uint8_t gParamsSaveEEPROMRequset=0;

#define EEPROM_DEFAULT_VERSION 1



 u8 RX_ADDRESS[10];


extern u8 NRFMatched;


void TableToParam(void)
{
    uint8_t i=0;
    for(i=0; i<3; i++)
    {
        ((float *)(&pitch_angle_PID))[i]=((float *)(&table.pidPitch))[i];
        ((float *)(&roll_angle_PID))[i]=((float *)(&table.pidRoll))[i];
        ((float *)(&yaw_angle_PID))[i]=((float *)(&table.pidYaw))[i];

        ((float *)(&pitch_rate_PID))[i]=((float *)(&table.pidPitchRate))[i];
        ((float *)(&roll_rate_PID))[i]=((float *)(&table.pidRollRate))[i];
        ((float *)(&yaw_rate_PID))[i]=((float *)(&table.pidYawRate))[i];

        ((float *)(&alt_PID))[i]=((float *)(&table.pidAlt))[i];
        ((float *)(&alt_vel_PID))[i]=((float *)(&table.pidAltVel))[i];

        imu.accOffset[i]=table.accOffset[i];
        imu.gyroOffset[i]=table.gyroOffset[i];



#ifdef NEW_ATTI_CTRL
        AttiCtrlParamsFromPIDTable();	//load to new ctrl param
#endif

    }
    for(i=0; i<5; i++) {
        ((u8 *)(&RX_ADDRESS))[i] = ((float *)(&table.NRFaddr))[i];


    }
  //  BTstate = table.BTstate;
    NRFMatched = table.NRFmatchFlag;

}


void ParamToTable(void)
{
    uint8_t i=0;
    float temp;
    for(i=0; i<3; i++)
    {
        ((float *)(&table.pidPitch))[i]=((float *)(&pitch_angle_PID))[i];
        temp=((float *)(&roll_angle_PID))[i];
        *((float *)(&table.pidRoll) + i) =  ((float *)(&roll_angle_PID))[i];
        ((float *)(&table.pidRoll))[i]=((float *)(&roll_angle_PID))[i];
        ((float *)(&table.pidYaw))[i]=((float *)(&yaw_angle_PID))[i];

        ((float *)(&table.pidPitchRate))[i]=((float *)(&pitch_rate_PID))[i];
        ((float *)(&table.pidRollRate))[i]=((float *)(&roll_rate_PID))[i];
        ((float *)(&table.pidYawRate))[i]=((float *)(&yaw_rate_PID))[i];

        ((float *)(&table.pidAlt))[i]=((float *)(&alt_PID))[i];
        ((float *)(&table.pidAltVel))[i]=((float *)(&alt_vel_PID))[i];


        table.accOffset[i]=imu.accOffset[i];
        table.gyroOffset[i]=imu.gyroOffset[i];
    }

    for(i=0; i<5; i++)
        ((float *)(&table.NRFaddr))[i] = ((u8 *)(&RX_ADDRESS))[i];

    //table.BTstate = BTstate;
   // table.NRFmatchFlag = NRFMatched;

}



//all default value
void ParamSetDefault(void)
{

#ifndef NEW_ATTI_CTRL
    pitch_angle_PID.P = 3.5;
    pitch_angle_PID.I = 0;//1.0;		//0
    pitch_angle_PID.D = 0;

    pitch_angle_PID.iLimit = 300;	//or 1000

    pitch_rate_PID.P  = 0.7;
    pitch_rate_PID.I  = 0.5; 		//0.5
    pitch_rate_PID.D  = 0.03;

    pitch_rate_PID.iLimit = 300;
////////////////////////////////////////////
    roll_angle_PID.P = 3.5;
    roll_angle_PID.I = 0;//1.0;
    roll_angle_PID.D = 0;
    roll_angle_PID.iLimit = 300;	//or 1000

    roll_rate_PID.P  = 0.7;
    roll_rate_PID.I  = 0.5;; 	//0.5
    roll_rate_PID.D  = 0.03;
    roll_rate_PID.iLimit = 300;
///////////////////////////////////////////
    yaw_angle_PID.P = 1;
    yaw_angle_PID.I = 0.2;
    yaw_angle_PID.D = 0;

    yaw_rate_PID.P  = 20;
    yaw_rate_PID.I  = 0;
    yaw_rate_PID.D  = 0;
#else
    AttiCtrlParamsSetDefault();
#endif
//
    alt_PID.P=1.0;
    alt_PID.I=0;
    alt_PID.D=0;

    alt_vel_PID.P=0.1f;
    alt_vel_PID.I=0.02f;
    alt_vel_PID.D=0;

    //should chango to read eeprom cfg. should be 0.
    imu.accOffset[0]=0;
    imu.accOffset[1]=0;
    imu.accOffset[2]=0;

    imu.gyroOffset[0]=0;
    imu.gyroOffset[1]=0;
    imu.gyroOffset[2]=0;

//		AttiCtrlParamsFromPIDTable();

}

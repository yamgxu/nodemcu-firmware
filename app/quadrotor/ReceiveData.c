/*    
      ____                      _____                  +---+
     / ___\                     / __ \                 | R |
    / /                        / /_/ /                 +---+
   / /   ________  ____  ___  / ____/___  ____  __   __
  / /  / ___/ __ `/_  / / _ \/ /   / __ \/ _  \/ /  / /
 / /__/ /  / /_/ / / /_/  __/ /   / /_/ / / / / /__/ /
 \___/_/   \__,_/ /___/\___/_/    \___ /_/ /_/____  /
                                                 / /
                                            ____/ /
                                           /_____/
ReceiveData.c file
编写者：小马  (Camel)
作者E-mail：375836945@qq.com
编译环境：MDK-Lite  Version: 4.23
初版时间: 2014-01-28
功能：
1.接收函数文件，包括接收2.4G数据，UART1的数据流
2.解析数据包，分配给对应的控制量
------------------------------------
*/

  
#include "ReceiveData.h"
#include "imu.h"

#include "MPU6050.h"
#include "extern_variable.h"
#include "Control.h"
#include "dmp.h"
#include "SysConfig.h"
#include "ConfigTable.h"

#define CONSTRAIN(x,min,max) {if(x<min) x=min; if(x>max) x=max;}
#define APP_YAW_DB	 70 //dead band
#define APP_PR_DB		 50

uint8_t 		FLY_ENABLE=0;//aircraft enable

RC_GETDATA  RC_DATA={0,0,0,0},RC_DATA_RAW={0,0,0,0};	// RC_DATA是处理后的期望四通

extern uint32_t lastGetRCTime;

//函数名：ReceiveDataFormNRF()
//输入：无
//输出: 无
//描述：将收到的2.4G遥控数据赋值给对应的变量
//作者：马骏
//void ReceiveDataFormNRF(void)
//{
//
//    //飞机电池过放，处于自动降落状态
//    //对遥控数据不再响应，使用归中值
//    if(LANDING == altCtrlMode) {
//        rcData[THROTTLE] = 1500;
//        rcData[YAW] = 1500;
//        rcData[PITCH] = 1500;
//        rcData[ROLL] = 1500;
//    }
//
//    CONSTRAIN(rcData[THROTTLE],1000,2000);
//    CONSTRAIN(rcData[YAW],1000,2000);
//    CONSTRAIN(rcData[PITCH],1000,2000);
//    CONSTRAIN(rcData[ROLL],1000,2000);
//
//    RC_DATA.THROTTLE=rcData[THROTTLE]-1000;
//    RC_DATA.YAW= YAW_RATE_MAX * dbScaleLinear((rcData[YAW] - 1500),500,APP_YAW_DB);
//    RC_DATA.PITCH= Angle_Max * dbScaleLinear((rcData[PITCH] - 1500),500,APP_PR_DB);
//    RC_DATA.ROOL= Angle_Max * dbScaleLinear((rcData[ROLL] - 1500),500,APP_PR_DB);
//
//}

/*****NRF24L01 match *****/
static uint8_t sta;
//extern u8  RX_ADDRESS[10];
u8 NRFMatched = 0;




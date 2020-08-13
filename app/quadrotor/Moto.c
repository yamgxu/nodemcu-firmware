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
moto.c file
编写者：小马  (Camel)
作者E-mail：375836945@qq.com
编译环境：MDK-Lite  Version: 4.23
初版时间: 2014-01-28
功能：
1.飞机上四路电机驱动PWM初始化
2.用定时器2的PWM输出模式
------------------------------------
*/

#include "moto.h"
#include "platform.h"
#include <stdint.h>

int16_t MOTO1_PWM = 0;
int16_t MOTO2_PWM = 0;
int16_t MOTO3_PWM = 0;
int16_t MOTO4_PWM = 0;
/***********************************************
函数名：MotorPwmFlash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
功能：更新四路PWM值
输入参数：MOTO1_PWM,MOTO2_PWM,MOTO3_PWM,MOTO4_PWM
输出:无
描述：四路PWM由定时器2输出，输入范围0-999
备注：
***********************************************/
void MotorPwmFlash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
{		
     if(MOTO1_PWM>=Moto_PwmMax)	MOTO1_PWM = Moto_PwmMax;
     if(MOTO2_PWM>=Moto_PwmMax)	MOTO2_PWM = Moto_PwmMax;
     if(MOTO3_PWM>=Moto_PwmMax)	MOTO3_PWM = Moto_PwmMax;
     if(MOTO4_PWM>=Moto_PwmMax)	MOTO4_PWM = Moto_PwmMax;
     if(MOTO1_PWM<=0)	MOTO1_PWM = 0;
     if(MOTO2_PWM<=0)	MOTO2_PWM = 0;
     if(MOTO3_PWM<=0)	MOTO3_PWM = 0;
     if(MOTO4_PWM<=0)	MOTO4_PWM = 0;//限定输入不能小于0，大于999
     platform_pwm_set_duty( 1, MOTO1_PWM );
     platform_pwm_set_duty( 2, MOTO2_PWM );
     platform_pwm_set_duty( 3, MOTO3_PWM);
     platform_pwm_set_duty( 4, MOTO4_PWM );

}

/***********************************************
函数名：MotorInit(void)
功能：输出PWM的定时器2初始化
输入参数：无
输出:无
描述：调用该函数，即初始化定时器2为PWM输出模式
备注：
***********************************************/
void MotorInit(void)
{
     platform_pwm_setup( 1, 100, 10 );
     platform_pwm_setup( 2, 100, 10 );
     platform_pwm_setup( 3, 100, 10 );
     platform_pwm_setup( 4, 100, 10 );
     platform_pwm_start( 1 );
     platform_pwm_start( 2 );
     platform_pwm_start( 3 );
     platform_pwm_start( 4 );
    return ;
}

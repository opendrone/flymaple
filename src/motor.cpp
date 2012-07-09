/**
 * @file   motor.cpp
 * @author tonghuix <tonghuix@tonghuix-1011PX>
 * @date   Sat May 19 16:40:38 2012
 * 
 * @brief  Motor Control Functions
 * 
 * 
 */

#include "motor.h"
#include "config.h"
#include "main.h"

///////////////////////////////电机控制方法//////////////////////////////////
//通过中断产生4个电机控制信号，首先将电机信号量从小到大排序进行排序
//计算电机控制量之间的差值，将差值赋给定时器，定时器计数到后进入中断
//将相同时间的电机端口置低
//KK四轴电机控制发出信号：
//周期：2.08MS
//在油门最小位置高电平：1.02ms
//中间位置：1.46ms
//最高位置：1.96MS
//当开电的时候给电调的信号是常低电平，当通过遥控器开启后，给电机控制的信号是1040US
//这时电机不转动
/////////////////////////////////////////////////////////////////////////////

///////////////////////电机控制端口定义/////////////////////////////////////////
#define	MOTOR0PIN  D28  //电机0控制端口 数字口D28
#define	MOTOR1PIN  D27  //电机1控制端口 数字口D27
#define	MOTOR2PIN  D11  //电机2控制端口 数字口D11
#define	MOTOR3PIN  D12  //电机3控制端口 数字口D12


//4个电机的控制信号量，值范围：1-999us 代表电机转速停止到最大速度
//当设置为0时将PWM占空比调整到0%，接口常低电平，当为1000时PWM占空比100%，接口常高电平。
uint16 MotorData[4] = {0,0,0,0};

////////////////////////////////////////////////////////////////////////////////////
//函数原型:  void motorCcontrol(void)                 	     
//参数说明:  无                                        
//返回值:    无                                                               
//说明:      电机控制函数将电机控制值量计算出PWM控制信号
///////////////////////////////////////////////////////////////////////////////////
void motorCcontrol(void)    
{
  uint16 PWMData[4] = {0,0,0,0};
  uint8 i;
  for(i=0;i<4;i++)
  {
    if(MotorData[i] <= 0)  PWMData[i] = 0;  //PWM占空比调整到0%，接口常低电平。
      else if(MotorData[i]  >= 1000) PWMData[i] = 50000;  //PWM占空比100%，接口常高电平。
        else  PWMData[i] = (1000 + MotorData[i])*24;
  }     
  //PWM最小1，最大499921，每24个数值对应1US，单值为0时为占空比为0%，当大于499920时为占空比100%
  pwmWrite(MOTOR0PIN,PWMData[0] );
  pwmWrite(MOTOR1PIN,PWMData[1] );
  pwmWrite(MOTOR2PIN,PWMData[2] );
  pwmWrite(MOTOR3PIN,PWMData[3] );
}

////////////////////////////////////////////////////////////////////////////////////
//函数原型:  void motorInit(void)                                      	     
//参数说明:  无                                        
//返回值:    无                                                               
//说明:      初始化电机控制
///////////////////////////////////////////////////////////////////////////////////
void motorInit(void)   
{
  //将4个电机控制管脚都设置为推挽输出IO
  pinMode(MOTOR0PIN, PWM);
  pinMode(MOTOR1PIN, PWM);
  pinMode(MOTOR2PIN, PWM);
  pinMode(MOTOR3PIN, PWM);
  Timer3.setPeriod(2080);  //数字口D28，D27，D11，D12是Timer3的4个比较输出口，将Timer3的周期设置为2080us,电机更新频率为500HZ
  MotorData[0] = 0;
  MotorData[1] = 0;
  MotorData[2] = 0;
  MotorData[3] = 0;
  motorCcontrol();   //计算各个电机控制量之差,将这个值用于定时器产生中断改变相应电机脉冲高电平时间   
 }
 
 void motorStop(){
  MotorData[0] = 1;
  MotorData[1] = 1;
  MotorData[2] = 1;
  MotorData[3] = 1;
  motorCcontrol();   //计算各个电机控制量之差,将这个值用于定时器产生中断改变相应电机脉冲高电平时间 
 }
 
 void motorHalf(){
  MotorData[0] = 300;
  MotorData[1] = 300;
  MotorData[2] = 300;
  MotorData[3] = 300;
  motorCcontrol();   //计算各个电机控制量之差,将这个值用于定时器产生中断改变相应电机脉冲高电平时间
 }
 
 void motorCustom(int pwm0, int pwm1, int pwm2, int pwm3){
  MotorData[0] = pwm0;
  MotorData[1] = pwm1;
  MotorData[2] = pwm2;
  MotorData[3] = pwm3;
  motorCcontrol();   //计算各个电机控制量之差,将这个值用于定时器产生中断改变相应电机脉冲高电平时间
 }
   
   


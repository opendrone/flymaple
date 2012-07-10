/**
 * @file   CapturePPM.cpp
 * @author tonghuix <tonghuix@tonghuix-Studio-1450>
 * @date   Tue Jul 10 08:11:24 2012
 * 
 * @brief  PPM remote control
 * 
 * 
 */

#include "wirish.h"
#include "misc.h"
#include "config.h"
#include "CapturePPM.h"


//定义捕获变量，这些值在PPM改变时改变

volatile unsigned int chan1begin = 0;  //记录开始值
volatile unsigned int chan1end   = 0;  //记录结束值
volatile unsigned int chan1PPM  = 0;  //采集到的PPM脉宽值

volatile unsigned int chan2begin = 0;
volatile unsigned int chan2end   = 0;
volatile unsigned int chan2PPM  = 0;  //采集到的PPM脉宽值

volatile unsigned int chan3begin = 0;
volatile unsigned int chan3end   = 0;
volatile unsigned int chan3PPM  = 0;  

volatile unsigned int chan4begin = 0;
volatile unsigned int chan4end   = 0;
volatile unsigned int chan4PPM  = 0;


////////////////////////////////////////////////////////////////////////////////////
//函数原型:  void capturePPMInit(void)                                   	     
//参数说明:  无                                        
//返回值:    无                                                               
//说明:      捕获遥控器接收机PPM输入信号功能初始化
///////////////////////////////////////////////////////////////////////////////////
void capturePPMInit(void)   
{
  // 设置连接航模RC接收器的管脚为输入   Set up the RC receiver pins as inputs
  pinMode(Channel1Pin, INPUT);
  pinMode(Channel2Pin, INPUT);
  pinMode(Channel3Pin, INPUT);
  pinMode(Channel4Pin, INPUT);

  //定义外部中断引脚及其对应的中断服务函数，当事件发生跳转到相应函数
  attachInterrupt(Channel1Pin,handler_CH1,CHANGE);  //定义通道1管脚为电平变化中断，中断函数为handler_CH1
  attachInterrupt(Channel2Pin,handler_CH2,CHANGE);
  attachInterrupt(Channel3Pin,handler_CH3,CHANGE);
  attachInterrupt(Channel4Pin,handler_CH4,CHANGE);  
}
////////////////////////////////////////////////////////////////////////////////////
//函数原型:  void handler_CH1(void)                                   	     
//参数说明:  无                                        
//返回值:    无                                                               
//说明:      PPM输入通道1电平变化中断函数，测量后作为 Pitch （俯仰）控制参数
///////////////////////////////////////////////////////////////////////////////////
void handler_CH1(void)
{  
  unsigned int total = 0;  //记录总和最终结果
  if(digitalRead(Channel1Pin)  == 1)  //如果是上升沿
  {
    chan1begin = micros(); 
  }  
  else
  {
    if(chan1begin != 0)  //如果等于0说明上升沿还没有捕获到不做处理
    {
       chan1end = micros();
      total = chan1end - chan1begin;
      if((total > 950) && (total < 2000)) //如果捕捉到脉宽在PPM范围内的信号就更新
      {
        chan1PPM = total;
      }
      chan1begin = 0;
     }
  }
}    
////////////////////////////////////////////////////////////////////////////////////
//函数原型:  void handler_CH2(void)                                   	     
//参数说明:  无                                        
//返回值:    无                                                               
//说明:      PPM输入通道2电平变化中断函数，测量后作为 Roll（横滚）控制参数
///////////////////////////////////////////////////////////////////////////////////
void handler_CH2(void) 
{              
  unsigned int total = 0;  //记录总和最终结果
  if(digitalRead(Channel2Pin)  == 1)  //如果是上升沿
  {
    chan2begin = micros(); 
  }  
  else
  {
    if(chan2begin != 0)  //如果等于0说明上升沿还没有捕获到不做处理
    {
       chan2end = micros();
      total = chan2end - chan2begin;
      if((total > 950) && (total < 2000)) //如果捕捉到脉宽在PPM范围内的信号就更新
      {
        chan2PPM = total;
      }
      chan2begin = 0;
     }
  }
} 
////////////////////////////////////////////////////////////////////////////////////
//函数原型:  void handler_CH3(void)                                   	     
//参数说明:  无                                        
//返回值:    无                                                               
//说明:      PPM输入通道3电平变化中断函数，测量后作为 Throttle（油门）控制参数
///////////////////////////////////////////////////////////////////////////////////
void handler_CH3(void) 
{              
  unsigned int total = 0;  //记录总和最终结果
  if(digitalRead(Channel3Pin)  == 1)  //如果是上升沿
  {
    chan3begin = micros(); 
  }  
  else
  {
    if(chan3begin != 0)  //如果等于0说明上升沿还没有捕获到不做处理
    {
       chan3end = micros();
      total = chan3end - chan3begin;
      if((total > 950) && (total < 2000)) //如果捕捉到脉宽在PPM范围内的信号就更新
      {
        chan3PPM = total;
      }
      chan3begin = 0;
     }
  }
}     
////////////////////////////////////////////////////////////////////////////////////
//函数原型:  void handler_CH4(void)                                   	     
//参数说明:  无                                        
//返回值:    无                                                               
//说明:      PPM输入通道4电平变化中断函数，测量后作为 Yaw（偏航，绕Z轴旋转）控制参数
///////////////////////////////////////////////////////////////////////////////////
void handler_CH4(void)
{              
  unsigned int total = 0;  //记录总和最终结果
  if(digitalRead(Channel4Pin)  == 1)  //如果是上升沿
  {
    chan4begin = micros(); 
  }  
  else
  {
    if(chan4begin != 0)  //如果等于0说明上升沿还没有捕获到不做处理
    {
       chan4end = micros();
      total = chan4end - chan4begin;
      if((total > 950) && (total < 2000)) //如果捕捉到脉宽在PPM范围内的信号就更新
      {
        chan4PPM = total;
      }
      chan4begin = 0;
     }
  }
}  


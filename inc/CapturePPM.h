/**
 * @file   CapturePPM.h
 * @author tonghuix <tonghuix@tonghuix-Studio-1450>
 * @date   Tue Jul 10 08:12:35 2012
 * 
 * @brief  PPM remote control header
 * 
 * 
 */

#ifndef __PPM__
#define __PPM__

////////////////PPM 信号参数定义///////////////////////////////////////////////////
#define	PPM_MAX		1000
#define PPM_MIN		-125
#define PPM_HIGH	100
#define PPM_LOW		-100
#define PPM_SIG_HIGH	2000
#define PPM_SIG_NEU	1500
#define PPM_SIG_LOW	1000

// 选项定义
#define	STICKGATE	 70	// Stick move gate when setting 设置时的摇杆摆动门限
#define SOFT_IDLE	 0X02
#define SOFT_EXP	 0X01
#define SOFT_FLT	 0X00

#define AXIS_CROSS	 0X00	//十字模式
#define AXIS_X		 0XFF	//X模式


void capturePPMInit(void);
void handler_CH1(void);
void handler_CH2(void) ;
void handler_CH3(void);
void handler_CH4(void);


#endif

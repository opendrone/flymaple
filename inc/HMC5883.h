/**
 * @file   HMC5883.h
 * @author tonghuix <tonghuix@tonghuix-Studio-1450>
 * @date   Tue Jul 10 05:43:19 2012
 * 
 * @brief  Compass Header
 * 
 * 
 */

#ifndef __HMC5883__
#define __HMC5883__


///////////////////////////HMC5883电子罗盘///////////////////////////////
#define HMC5883_ADDR 0x1E // 7 bit address of the HMC5883 used with the Wire library HMC5883 地址

// HMC5883 寄存器定义
#define HMC5883_R_CONFA 0  //Configuration Register A   Read/Write 
#define HMC5883_R_CONFB 1  //Configuration Register B   Read/Write 
#define HMC5883_R_MODE 2   //Mode Register  Read/Write 
#define HMC5883_R_XM 3    //Data Output X MSB Register  Read
#define HMC5883_R_XL 4    //Data Output X LSB Register  Read
#define HMC5883_R_ZM 5    //Data Output Z MSB Register  Read 
#define HMC5883_R_ZL 6    //Data Output Z LSB Register  Read 
#define HMC5883_R_YM 7    //Data Output Y MSB Register  Read 
#define HMC5883_R_YL 8    //Data Output Y LSB Register  Read
#define HMC5883_R_STATUS 9 //Status Register  Read 
#define HMC5883_R_IDA 10   // Identification Register A  Read
#define HMC5883_R_IDB 11   //Identification Register B  Read  
#define HMC5883_R_IDC 12   //Identification Register C  Read

void compassInit(uint8 setmode);
void commpassSetMode(uint8 mode) ;
void compassCalibrate(uint8 gain) ;
void compassSetDOR(uint8 DOR);
void compassSetGain(uint8 gain);
void compassRead(int16 * result) ;
double compassHeading(void);


#endif

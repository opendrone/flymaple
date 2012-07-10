/**
* @file   ADXL345.pde
* @author tonghuix <tonghuix@tonghuix-1011PX>
* @date   Thu Apr 12 16:30:46 2012
* 
* @brief  Acceleratemeter
* 
* 
*/

#include "ADXL345.h"
#include "wirish.h"
#include "config.h"
#include "misc.h"

void initAcc() {
    /* all i2c transactions send and receive arrays of i2c_msg objects */
  i2c_msg msgs[1]; // we dont do any bursting here, so we only need one i2c_msg object
  uint8 msg_data[2];
  msg_data = {0x00,0x00};
  msgs[0].addr = ACC;
  msgs[0].flags = 0; 
  msgs[0].length = 1; // just one byte for the address to read, 0x00
  msgs[0].data = msg_data;
  
  i2c_master_xfer(I2C1, msgs, 1,0);
  msgs[0].addr = ACC;
  msgs[0].flags = I2C_MSG_READ; 
  msgs[0].length = 1; // just one byte for the address to read, 0x00
  msgs[0].data = msg_data;
  i2c_master_xfer(I2C1, msgs, 1,0);
  /* now we check msg_data for our 0xE5 magic number */
  uint8 dev_id = msg_data[0];
  //SerialUSB.print("Read device ID from xl345: ");
  //SerialUSB.println(dev_id,HEX);
  
  if (dev_id != XL345_DEVID) {
    SerialUSB.println("Error, incorrect xl345 devid!");
    SerialUSB.println("Halting program, hit reset...");
    waitForButtonPress(0);
  }
  //调用 ADXL345
  writeTo(ACC, ADXLREG_POWER_CTL, 0x00); //清零 
  writeTo(ACC, ADXLREG_POWER_CTL, 0xff);//休眠
  writeTo(ACC, ADXLREG_POWER_CTL, 0x08); //仅开启工作模式
  //设定在 +-2g 时的默认读数
}

void getAccelerometerData(int16 * result) {
  int16 regAddress = ADXLREG_DATAX0;    //加速度传感器ADXL345第一轴的数据地址
  uint8 buff[A_TO_READ];

  readFrom(ACC, regAddress, A_TO_READ, buff); //读取加速度传感器ADXL345的数据

  //每个轴的读数有10位分辨率，即2个字节.  
  //我们要转换两个bytes为一个int变量
  result[0] = (((int16)buff[1]) << 8) | buff[0] + a_offx;   
  result[1] = (((int16)buff[3]) << 8) | buff[2] + a_offy;
  result[2] = (((int16)buff[5]) << 8) | buff[4] + a_offz;
}

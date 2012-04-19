/* BMP085 Extended Example Code
  by: Jim Lindblom
  SparkFun Electronics
  date: 1/18/11
  license: CC BY-SA v3.0 - http://creativecommons.org/licenses/by-sa/3.0/
  
  Get pressure and temperature from the BMP085 and calculate altitude.
  Serial.print it out at 9600 baud to serial monitor.

  Update (7/19/11): I've heard folks may be encountering issues
  with this code, who're running an Arduino at 8MHz. If you're 
  using an Arduino Pro 3.3V/8MHz, or the like, you may need to 
  increase some of the delays in the bmp085ReadUP and 
  bmp085ReadUT functions.
*/

#include "BMP085.h"
#include "wirish.h"
#include "misc.h"

const uint8 OSS = 0;  // Oversampling Setting


// Calibration values
int16 ac1;
int16 ac2; 
int16 ac3; 
uint16 ac4;
uint16 ac5;
uint16 ac6;
int16 b1; 
int16 b2;
int16 mb;
int16 mc;
int16 md;

// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
int32 b5; 

// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void bmp085Calibration()
{
  ac1 = bmp085ReadInt(BMP085_CAL_AC1);
  ac2 = bmp085ReadInt(BMP085_CAL_AC2);
  ac3 = bmp085ReadInt(BMP085_CAL_AC3);
  ac4 = bmp085ReadInt(BMP085_CAL_AC4);
  ac5 = bmp085ReadInt(BMP085_CAL_AC5);
  ac6 = bmp085ReadInt(BMP085_CAL_AC6);
  b1 = bmp085ReadInt(BMP085_CAL_B1);
  b2 = bmp085ReadInt(BMP085_CAL_B2);
  mb = bmp085ReadInt(BMP085_CAL_MB);
  mc = bmp085ReadInt(BMP085_CAL_MC);
  md = bmp085ReadInt(BMP085_CAL_MD);
}

// Calculate temperature given ut.
// Value returned will be in units of 0.1 deg C
int16 bmp085GetTemperature(uint16 ut)
{
  int32 x1, x2;
  
  x1 = (((int32)ut - (int32)ac6)*(int32)ac5) >> 15;
  x2 = ((int32)mc << 11)/(x1 + md);
  b5 = x1 + x2;

  return ((b5 + 8)>>4);  
}

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
int32 bmp085GetPressure(uint32 up)
{
  int32 x1, x2, x3, b3, b6, p;
  uint32 b4, b7;
  
  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((int32)ac1)*4 + x3)<<OSS) + 2)>>2;
  
  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (uint32)(x3 + 32768))>>15;
  
  b7 = ((uint32)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;
    
  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;
  
  return p;
}
int32 bmp085GetAltitude(void)  //获得海拔高度，单位厘米
{
  int32 pressure = 0;
  int32 centimeters = 0;
  pressure = bmp085GetPressure(bmp085ReadUP());
  centimeters =  (int32)(44330 * (1 - pow(((float)pressure / (float)MSLP), 0.1903))) + Altitude_cm_Offset;  
  // converting from float to int32_t truncates toward zero, 100.999985 becomes 100 resulting in 1 cm error (max).
  return centimeters;
}
// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
int16 bmp085ReadInt(uint8 address)
{
  uint8 buff[2];
  readFrom(BMP085_ADDRESS, address, 2, buff);
  return ((((int16)buff[0]) << 8) | buff[1]);
}

// Read the uncompensated temperature value
uint16 bmp085ReadUT()
{
  uint16 ut;
   // Write 0x2E into Register 0xF4
  // This requests a temperature reading
  writeTo(BMP085_ADDRESS, BMP085_CONTROL, READ_TEMPERATURE); //
  // Wait at least 4.5ms
  delay(5);
  
  // Read two bytes from registers 0xF6 and 0xF7
  ut = bmp085ReadInt(BMP085_CONTROL_OUTPUT);
  return ut;
}

// Read the uncompensated pressure value
uint32 bmp085ReadUP()
{
  uint8 buff[3];
  uint32 up = 0;
  
  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  writeTo(BMP085_ADDRESS, BMP085_CONTROL, (READ_PRESSURE + (OSS<<6))); //
  // Wait for conversion, delay time dependent on OSS
  delay(2 + (3<<OSS));
  
  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  readFrom(BMP085_ADDRESS, BMP085_CONTROL_OUTPUT, 3, buff);
  up = (((uint32) buff[0] << 16) | ((uint32) buff[1] << 8) | (uint32) buff[2]) >> (8-OSS);
  return up;
}

#include "wirish.h"
#include "Pressure.h"

Pressure Pressure::pressure;
const unsigned char Pressure::PressureAddress = 0x77;
const unsigned char Pressure::OSS = 0;
const unsigned char Pressure::BMP085_CAL_AC[6] = {0xaa,0xac,0xae,0xb0,0xb2,0xb4};
const unsigned char Pressure::BMP085_CAL_B[2] = {0xb6,0xb8};
const unsigned char Pressure::BMP085_CAL_MB = 0xba;
const unsigned char Pressure::BMP085_CAL_MC = 0xbc;
const unsigned char Pressure::BMP085_CAL_MD = 0xbe;
const unsigned char Pressure::BMP085_CONTROL = 0xf4;
const unsigned char Pressure::BMP085_CONTROL_OUTPUT = 0xf6;
const unsigned char Pressure::READ_TEMPERATURE = 0x2e;
const unsigned char Pressure::READ_PRESSURE = 0x34;
const int Pressure::MSLP = 101325;
const int Pressure::Altitude_cm_Offset = 0;
short Pressure::ac[6],Pressure::b[2],Pressure::mb,Pressure::mc,Pressure::md;
int Pressure::b5;

Pressure::Pressure()
{
	for(int i = 0 ; i < 6 ; i++) ac[i] = read(BMP085_CAL_AC[i]);
	for(int i = 0 ; i < 2 ; i++) b[i] = read(BMP085_CAL_B[i]);
	mb = read(BMP085_CAL_MB);
	mc = read(BMP085_CAL_MC);
	md = read(BMP085_CAL_MD);
}

Pressure::~Pressure()
{
}

Vector<double> Pressure::getReading()
{
	unsigned int up; unsigned short ut;
	pressure.getRawReading(up,ut);
	int pres = pressure.rawToPressure(up);
	short temp = pressure.rawToTemperature(ut);
	double altitude = pressure.pressureToAltitude(pres);
	Vector<double> retVal(3);
	retVal(0) = pres; retVal(1) = temp; retVal(2) = altitude;
	return retVal;
}

short Pressure::read(unsigned char addr)
{
	unsigned char buffer[2];
	pressure.read(PressureAddress,addr,2,buffer);
	return ((((short)buffer[0]) << 8) | buffer[1]);
}

void Pressure::getRawReading(unsigned int& up,unsigned short& ut)
{
	//读气压
	unsigned char buffer[3];
	up = 0;
	pressure.write(PressureAddress,BMP085_CONTROL,(READ_PRESSURE + (OSS << 6)));
	delay(2 + (3 << OSS));
	pressure.read(PressureAddress,BMP085_CONTROL_OUTPUT,3,buffer);
	up = (((unsigned int) buffer[0] << 16) | ((unsigned int) buffer[1] << 8) | (unsigned int) buffer[2]) >> (8-OSS);
	//读温度
	pressure.write(PressureAddress,BMP085_CONTROL,READ_TEMPERATURE);
	delay(5);
	pressure.read(PressureAddress,BMP085_CONTROL_OUTPUT,2,buffer);
	ut = ((((short)buffer[0]) << 8) | buffer[1]);
}

int Pressure::rawToPressure(unsigned int up)
{
    int x1, x2, x3, b3, b6, p;
    unsigned int b4, b7;
  
    b6 = b5 - 4000;
    // Calculate B3
    x1 = (b[1] * (b6 * b6)>>12)>>11;
    x2 = (ac[1] * b6)>>11;
    x3 = x1 + x2;
    b3 = (((((int)ac[0])*4 + x3)<<OSS) + 2)>>2;
  
    // Calculate B4
    x1 = (ac[2] * b6)>>13;
    x2 = (b[0] * ((b6 * b6)>>12))>>16;
    x3 = ((x1 + x2) + 2)>>2;
    b4 = (ac[3] * (unsigned int)(x3 + 32768))>>15;
  
    b7 = ((unsigned int)(up - b3) * (50000>>OSS));
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

short Pressure::rawToTemperature(unsigned short ut)
{
    int x1, x2;
  
    x1 = (((int)ut - (int)ac[5])*(int)ac[4]) >> 15;
    x2 = ((int)mc << 11)/(x1 + md);
    b5 = x1 + x2;

    return ((b5 + 8)>>4); 
}

double Pressure::pressureToAltitude(int pressure)
{
	double meters =  (44330 * (1 - pow(((float)pressure / (float)MSLP), 0.1903))) + Altitude_cm_Offset;
	return meters;
}

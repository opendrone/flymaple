#ifndef SENSOR_H
#define SENSOR_H

#include "Vector.h"

class Sensor {
	static Sensor sensor;
	Sensor();
public:
	Sensor(const Sensor & sensors);
	~Sensor();
	static void read(unsigned char dev_addr,unsigned char read_addr,unsigned char read_length,unsigned char * buffer);
	static void write(unsigned char dev_addr,unsigned char write_addr,unsigned char value);
};

#endif

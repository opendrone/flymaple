#ifndef SENSOR_H
#define SENSOR_H

/**
 * @file   Sensor.h
 * @author breadbread1984 <breadbread1984@163.com>
 * @date   Sat Jul 21 15:12:00 2012
 * 
 * @brief	The static class contains important initialization code and basic routines.
 * 
 * The static class contains important initialization code and basic routines. 
 * All classes writing or reading from I2C bus should inherit from this class
 * to ensure the I2C bus is initialized before any access.
 * 
 * @copyright GPLv3
 */

#include "Vector.h"

class Sensor {
	static Sensor sensor;
	static bool isInit;
public:
	/**
	 * Destructor that does nothing.
	 */
	~Sensor();
protected:
	/**
	 * Constructor that does important initialization to enable all sensors.
	 * To do the initialization for only once, the constructor is hide from developer.
	 * The only one Sensor object is a static one created automatically.
	 */
	Sensor();
	/**
	 * Read data from a specific register on a desinated device. 
	 * 
	 * @param dev_addr device address on the i2c bus.
	 * @param read_addr register identifier.
	 * @param read_length the length of data read from the device.
	 * @param buffer a pre-alloced place where the data will be stored.
	 */
	void read(unsigned char dev_addr,unsigned char read_addr,unsigned char read_length,unsigned char * buffer);
	/**
	 * Write one byte to a specific register on a designated device.
	 * 
	 * @param dev_addr device address on the i2c bus.
	 * @param write_addr register identifier.
	 * @param value one byte data that will be write to the device.
	 */
	void write(unsigned char dev_addr,unsigned char write_addr,unsigned char value);
};

#endif

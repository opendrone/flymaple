#ifndef COMPASS_H
#define COMPASS_H

/**
 * @file   Compass.h
 * @author breadbread1984 <breadbread1984@163.com>
 * @date   Sat Jul 21 15:12:00 2012
 * 
 * @section DESCRIPTION 
 * 
 * The static class for manipulating the compass. 
 * 
 * @section LICENSE
 * 
 * GPLv3 
 */

#include "Sensor.h"

class Compass {
	static Compass compass;
	
	static const unsigned char CompassAddress;
	static const short sign[3];
	static const double scale[3];
	
	/**
	 * Constructor initializing the compass.
	 * To do the initialization for only once, the constructor is hiden from developer.
	 * The only one Compass object is a static one created automatically.
	 */
	Compass(unsigned char gain = 5);
	void getRawReading(short& x,short& y,short& z);
public:
	/**
	 * Destructor.
	 */
	~Compass();
	/**
	 * Get the direction of the noth magnetic pole.
	 * 
	 * @return the vector the north magnetic pole. Please notice that the direction 
	 * points to a point below the northern horizon in the northern hemisphere. 
	 * It is not a horizontal vector.
	 */
	static Vector<double> getReading();
	/**
	 * Prints the calibration information for off-line calibration. The calibration 
	 * is needed only once for a specific compass. The user need to place this function
	 * in a infinite loop. When the program runs, the scalex, scaley and scalez are
	 * printed to the serial. The user need rotate the flymaple till the reading on 
	 * the serial stablizes. Then the record the readings to Compass::scale[3] in 
	 * Compass.cpp. Last, recompile the program. Calibration accomplished.
	 */
	static void calibrate(unsigned char gain = 5);
};

#endif

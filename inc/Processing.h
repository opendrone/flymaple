#ifndef __PROC__
#define __PROC__

void processing(int16 * acc, int16 * gyro);
float squared(float x) ;
void getInclination() ;
void getEstimatedInclination(unsigned int interval_us);
#endif

#ifndef INTERFACES4C_H
#define INTERFACES4C_H

#ifdef __cplusplus
extern "C" {
#endif

void getReadingFromAcc(double * data);
void getReadingFromComp(double * data);
void getReadingFromGyro(double * data);
void getReadingFromPres(double * data);
void getXYZ(double * X,double * Y,double * Z);
void getRPY(double * roll,double * pitch,double * yaw);

#ifdef __cplusplus
}
#endif

#endif

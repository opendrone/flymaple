#include "wirish.h"
#include "Test.h"
#include "GlobalXYZ.h"
#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Compass.h"
#include "Pressure.h"
#include "Motor.h"

void Test::testOrientationFiltering1()
{
	while(1) {
		Vector<double> quaternion = GlobalXYZ::getQuaternion();
		for(int i = 0 ; i < quaternion.size() ; i++) {
			float n = quaternion(i);
			unsigned char * ptr = reinterpret_cast<unsigned char*>(&n);
			for(int i = 0 ; i < sizeof(float) ; i++) {
				unsigned char b1 = (ptr[i] >> 4) & 0x0f;
				unsigned char b2 = (ptr[i] & 0x0f);
				char c1 = (b1 < 10) ? ('0' + b1) : 'A' + b1 - 10;
				char c2 = (b2 < 10) ? ('0' + b2) : 'A' + b2 - 10;
				SerialUSB.print(c1);
				SerialUSB.print(c2);
			}
			SerialUSB.print(",");
		}
		SerialUSB.println();
		vTaskDelay(300);
	}
}

void Test::testOrientationFiltering2()
{
	while(1) {
		double roll = 0,pitch = 0,yaw = 0;
		GlobalXYZ::getRPY(roll,pitch,yaw);
		roll *= 180 / 3.1415926; pitch *= 180 / 3.1415926; yaw *= 180 / 3.1415926;
		SerialUSB.print("roll = "); SerialUSB.print(roll); SerialUSB.print("\t");
		SerialUSB.print("pitch = "); SerialUSB.print(pitch); SerialUSB.print("\t");
		SerialUSB.print("yaw = "); SerialUSB.print(yaw); SerialUSB.print("\t");
		Vector<double> pressure = Pressure::getReading();
		SerialUSB.print("pressure = "); SerialUSB.print(pressure(0)); SerialUSB.print("pa\t");
		SerialUSB.print("temperature = "); SerialUSB.print(pressure(1) * 0.1); SerialUSB.print("C\t");
		SerialUSB.print("altitude = "); SerialUSB.print(pressure(2)); SerialUSB.print("m\t");
		toggleLED();
		SerialUSB.println();
		vTaskDelay(300);
	}
}

void Test::testAccelerometer()
{
	while(1) {
		Vector<double> retVal = Accelerometer::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0)); 
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1)); 
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));
		SerialUSB.println();
		vTaskDelay(300);
	}
}

void Test::testGyroscope()
{
	while(1) {
		Vector<double> retVal = Gyroscope::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0)); 
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1)); 
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));		
		SerialUSB.println();
		vTaskDelay(300);
	}
}

void Test::testCompass()
{
	while(1) {
		Vector<double> retVal = Compass::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0));
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1));
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));
		SerialUSB.println();
		vTaskDelay(300);
	}
}

void Test::testMotor()
{
	int selected = 0;
	int val = 2;
	Motor::control1(0);
	Motor::control2(0);
	Motor::control3(0);
	Motor::control4(0);
	vTaskDelay(100);
    SerialUSB.println("## NOTE: Press 1 ~ 4 to select motor, or Press 'a' for select All motors.");
    SerialUSB.println("##       Press 'j' for increace Motor, Press 'k' for motor Decrease.");
	SerialUSB.println();
	while(1) {
		SerialUSB.print("M1: ");
		displayThrottle(Motor::getLevel1());
		SerialUSB.println();
		SerialUSB.print("M2: ");
		displayThrottle(Motor::getLevel2());
		SerialUSB.println();
		SerialUSB.print("M3: ");
		displayThrottle(Motor::getLevel3());
		SerialUSB.println();
		SerialUSB.print("M4: ");
		displayThrottle(Motor::getLevel4());
		SerialUSB.println();
		SerialUSB.print("\033[A\033[A\033[A\033[A");
		while(!SerialUSB.available());
		char tch = SerialUSB.read();
		switch(tch) {
			case '1': selected = 1;  break;
            case '2': selected = 2;  break;
            case '3': selected = 3;  break;
            case '4': selected = 4;  break;
            case 'a': selected = 0;  break;
            case 'j': val += 50; break;
            case 'k': val -= 50; break;
            case 'r': return;
            default: 
				val = 0; 
				Motor::control1(val);
				Motor::control2(val);
				Motor::control3(val);
				Motor::control4(val); 
				break;
		}
		val = (val > 999)?999:((val < 0)?2:val);
		if(selected != 0) {
			switch(selected) {
				case 1: Motor::control1(val); break;
				case 2: Motor::control2(val); break;
				case 3: Motor::control3(val); break;
				case 4: Motor::control4(val); break;
				default:
					val = 0; 
					Motor::control1(val);
					Motor::control2(val);
					Motor::control3(val);
					Motor::control4(val); 
					break;
			}
		} else {
			Motor::control1(val);
			Motor::control2(val);
			Motor::control3(val);
			Motor::control4(val);
		}
	}
}

void Test::displayThrottle(int val)
{
    int i = 0;
    SerialUSB.print("\t");
    SerialUSB.print("\033[K"); 
    SerialUSB.print(val);
    SerialUSB.print("\t>>|");
    
    for(i = 0; i < 40; i++)
    {
        if(i <= val / 25) SerialUSB.print("|");
        else SerialUSB.print("-");
    }
    SerialUSB.print("|<<");
}

void vTaskTestOrientationFiltering1(void * pvParameters)
{
	Test::testOrientationFiltering1();
}

void vTaskTestOrientationFiltering2(void * pvParameters)
{
	Test::testOrientationFiltering2();
//	SerialUSB.println("hello");
//	vTaskDelay(900);
}

void vTaskTestAccelerometer(void * pvParameters)
{
	Test::testAccelerometer();
}

void vTaskTestGyroscope(void * pvParameters)
{
	Test::testGyroscope();
}

void vTaskTestCompass(void * pvParameters)
{
	Test::testCompass();
}

void vTasktestMotor(void * pvParameters)
{
	Test::testMotor();
}

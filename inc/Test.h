#ifndef TEST_H
#define TEST_H

class Test {
	static void displayThrottle(int val);
public:
	static void testOrientationFiltering1();
	static void testOrientationFiltering2();
	static void testAccelerometer();
	static void testGyroscope();
	static void testCompass();
	static void testMotor();
};

void vTaskTestOrientationFiltering1(void * pvParameters);
void vTaskTestOrientationFiltering2(void * pvParameters);
void vTaskTestAccelerometer(void * pvParameters);
void vTaskTestGyroscope(void * pvParameters);
void vTaskTestCompass(void * pvParameters);
void vTasktestMotor(void * pvParameters);

#endif

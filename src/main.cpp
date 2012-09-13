/**
 * @file   main.cpp
 * @author openDrone <opendrone@googlegroups.com>
 * @date   Wed Apr 11 22:59:22 2012
 * 
 * @brief  openDrone Quadcopter Main function File
 * @license GPLv3
 * 
 */


#include "main.h"
#include "flight.h"
#include "config.h"
#include "qctest.h"
#include "sensors.h"
#include "motor.h"

#define BS '\b'

unsigned long previousMillis = 0;

void setup()
{
    /* Set up the LED to blink  */
    pinMode(BOARD_LED_PIN, OUTPUT);

    /* Turn on PWM on pin PWM_PIN */
    pinMode(PWM_PIN, PWM);
    pwmWrite(PWM_PIN, 0x8000);

    /* Send a message out USART2  */
    Serial2.begin(9600);
    Serial2.println("Hello world!");

    motorInit();//电机控制初始化
    delay(300);
    i2c_master_enable(I2C1, 0); //i2c init
    delay(100);
    initAcc();    //Accelerometer Init
    delay(1000);
    initGyro();   //Gyroscope Init
    delay(100);
    bmp085Calibration();
    compassInit(0);   //初始化罗盘
//    compassCalibrate(1);  //校准一次罗盘，gain为1.3Ga
//    commpassSetMode(0);  //设置为连续测量模式 

    delay(100);
    capturePPMInit();
    delay(100);
    
    /* Send a message out the usb virtual serial port  */
    Serial2.println("Hello!");
    Serial2.println("Test1234567890!");
#if TOPLEVEL
    while(Serial2.read() != 'ACK')
    {
        Serial2.println('REQ');
    }
#endif
    
}


void loop()
{
    int i = BOOTDELAY;
    unsigned long interval = 1000;
    unsigned long currentMillis ;

    previousMillis = millis();

    SerialUSB.print("\n\rPress any key to enter [Test Mode]:  ");
    
    while(SerialUSB.available() == 0 && i >= 0)
    {
        currentMillis = millis();
        if(currentMillis - previousMillis > interval)
        {    
            // save the last time you blinked the LED 
            previousMillis = currentMillis;
            SerialUSB.print(BS);  
            SerialUSB.print(i, DEC);
            toggleLED();
            i--;
        }
    }

    if(i <= 0 )
    {
        SerialUSB.println("\n\r Entering [Flight Mode]...");
        flightMode(); 
        loop();
    }
    else {
        SerialUSB.println("\n\r Entering [Test Mode] ...");
        testMode();
    }
}

/* Please Do Not Remove & Edit Following Code */
#ifdef CLI
// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
#endif

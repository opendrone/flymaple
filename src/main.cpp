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
#include "i2c.h"
#include "config.h"
#include "qctest.h"
#include "ITG3205.h"
#include "ADXL345.h"
#include "BMP085.h"
#include "HMC5883.h"
#include "motor.h"

#define BS '\b'

unsigned long previousMillis = 0;        
unsigned long interval = 1000;           

void flightMode()
{
    SerialUSB.println(">> Flight Mode <<");
    //TODO
    return;
}


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
    initAcc();    //Accelerometer Init
    initGyro();   //Gyroscope Init
    bmp085Calibration();
    compassInit(false);   //初始化罗盘
//    compassCalibrate(1);  //校准一次罗盘，gain为1.3Ga
//    commpassSetMode(0);  //设置为连续测量模式 

    delay(100);

    /* Send a message out the usb virtual serial port  */
    SerialUSB.println("Hello!");
    SerialUSB.println("Test1234567890!");
}


void loop()
{
    int i = BOOTDELAY;
    char ch;
    
    delay(3000);

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
        flightMode(); //TODO
        loop();
    }
    else SerialUSB.println("\n\r Entering [Test Mode] ...");

    while(1)
    {
        do{
            SerialUSB.read();    
        }while(SerialUSB.available() != 0);

        toggleLED();
        delay(1000);
        
         /* clear screen for standard PTY terminal  "\033[1H\033[2J " */
        SerialUSB.println("\33[2J");
        
        SerialUSB.println("\n\r >> OpenDrone Flymaple 1.1 << ");
        SerialUSB.println("---------------------------------");
        SerialUSB.println("(s) Sensors Test");
        SerialUSB.println("(m) Motors Test");
        SerialUSB.println("(r) Remote Control Test");
        SerialUSB.println("(t) Take Off");
        SerialUSB.println("(l) Landing");
        SerialUSB.println("(?) Help - Print this screen");
        SerialUSB.println("(x) Reset");
        SerialUSB.println("================================");
        SerialUSB.print("Choose ( \"?\" for help): ");

        /* Echo Charactor */
        ch = SerialUSB.read(); 
        SerialUSB.println(ch);
        
        switch(ch)
        {
            case 's':  sensorsTest(); break;
            case 'm':  motorsTest(); break;
            case 'r':  remoteTest(); break;
            case 't':  qcTakeOff(); break;
            case 'l':  qcLanding(); break;
            case '?':  break;
            case 'x': loop(); //call itself for resetting
            default: break;
        }
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

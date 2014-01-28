/**
 * @file   main.cpp
 * @author breadbread1984 <breadbread1984@163.com>
 * @date   Sat Jul 21 15:12:00 2012
 * 
 * @section DESCRIPTION 
 * 
 * openDrone Quadcopter Main function File
 * 
 * @section LICENSE
 * 
 * GPLv3 
 */


#include "wirish.h"
#include "MapleFreeRTOS.h"
#include "Test.h"
#include "GlobalXYZ.h"

#define PWM_PIN 2
#define STACK_SIZE 200

void setup()
{
    /* Set up the LED to blink  */
    pinMode(BOARD_LED_PIN, OUTPUT);

    /* Turn on PWM on pin PWM_PIN */
    pinMode(PWM_PIN, PWM);
    pwmWrite(PWM_PIN, 0x8000);

    /* Send a message out USART2  */
    Serial2.begin(9600);
}

/* Please Do Not Remove & Edit Following Code */
int main(void) {
    setup();
    
	xTaskCreate(vTaskUpdateXYZ,(const signed char *)"GlobalXYZ",STACK_SIZE,NULL,1,NULL);
	xTaskCreate(vTaskTestOrientationFiltering2,(const signed char *)"testOrientationFiltering2",STACK_SIZE,NULL,1,NULL);
	
	vTaskStartScheduler();

    return 0;
}

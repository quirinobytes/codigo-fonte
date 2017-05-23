/*
* Title: Blinking LED example
* NOTE: Tested with Espressif FreeRTOS SDK v.1.4.0
* Copyright (c) 2016 Pratik Panda
* Designed for IoTBlocks Hardware
* (Website: http://www.PratikPanda.com)
*
* MIT License with additional clause:
* The author, Pratik Panda, must be notified if the source code is used
* in a commercial product or associated with any service that is not
* provided free of cost to the end user.The above copyright notice and
* this permission notice shall be included in all copies or substantial
* portions of the Software.
*
* Full License text:
* http://www.pratikpanda.com/iotblocks/iotblocks-code-license/
*/

//#include "esp_common.h"
#include "gpio.h"

// This task will execute forever and blink LED
// Note that internal high priority tasks still
// execute - such as WiFi stack routines
void LEDBlinkTask (void *pvParameters)
{
  while(1)
  {
    // Delay and turn on
    vTaskDelay (300/portTICK_RATE_MS);
    GPIO_OUTPUT_SET (12, 1);

    // Delay and LED off
    vTaskDelay (300/portTICK_RATE_MS);
    GPIO_OUTPUT_SET (12, 0);
  }
}

// User function
// All user code goes here.
// Note that the user function should exit and not block execution
void user_init(void)
{
    printf("SDK version:%s\n", system_get_sdk_version());

    // Config pin as GPIO12
    PIN_FUNC_SELECT (PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);

    // This task blinks the LED continuously
    xTaskCreate(LEDBlinkTask, (signed char *)"Blink", 256, NULL, 2, NULL);
}

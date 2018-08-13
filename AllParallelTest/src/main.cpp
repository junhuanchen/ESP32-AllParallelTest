#include <Arduino.h>

#include "freertos/FreeRTOS.h"

#include "unit_test_ws2812.hpp"
#include "unit_test_buzzer.hpp"
#include "unit_test_mpu9250.hpp"
#include "unit_test_adc.hpp"
#include "unit_test_ble.hpp"
#include "unit_test_wifi.hpp"

#define UNIT_TEST_DEFINE(Name) static void unit_test_##Name(void *param) { Name##_setup(); while(true) printf("\n"), Name##_loop(); vTaskDelete(NULL); }

#define UNIT_TEST_CREATE(Name, Priority, StackSize, Cpu) xTaskCreatePinnedToCore(unit_test_##Name, "unit_test_##Name", StackSize, NULL, Priority, NULL, Cpu)

UNIT_TEST_DEFINE(ws2812);
UNIT_TEST_DEFINE(mpu9250);
UNIT_TEST_DEFINE(adc);
UNIT_TEST_DEFINE(buzzer);
UNIT_TEST_DEFINE(ble);
UNIT_TEST_DEFINE(wifi);

void setup()
{ 
    UNIT_TEST_CREATE(wifi, 6, 8192, 0);
    // delay(1000);
    UNIT_TEST_CREATE(mpu9250, 4, 2048, 0);
    // delay(1200);
    UNIT_TEST_CREATE(ws2812, 5, 2048, 0);
    // delay(1400);
    UNIT_TEST_CREATE(ble, 3, 2048, 0);
    // delay(1600);
    UNIT_TEST_CREATE(buzzer, 2, 2048, 0);
    // delay(1800);
    UNIT_TEST_CREATE(adc, 1, 2048, 0);
}

void loop()
{
    
}
#include <Arduino.h>
#include <driver/adc.h>
#include <esp_timer.h>

void get_light()
{
    int adc0 = adc1_get_raw(ADC1_CHANNEL_0); //获取转换后的数据
    int adc3 = adc1_get_raw(ADC1_CHANNEL_3);
    // double lux1 = (adc0 + 1) * (1.1 / 4096); //转换成电压
    // double lux2 = (adc3 + 1) * (1.1 / 4096);

    Serial.printf("get lux1=%d lux2=%d \n", adc0, adc3);

    // Serial.printf("get light left=%lf right=%lf \n", lux1, lux2);
}

void get_temperature()
{
    int adc6 = adc1_get_raw(ADC1_CHANNEL_6);       //获取转换后的数据
    
    // double v = (adc6 + 1) * (3.9 / 4096);        //转换成电压
    // double t = (3.3 - v) / (v / 4700.0);  //算出热敏电阻的温度
    Serial.printf("get temperature=%d \n", adc6);
    // Serial.printf("get voltage=%lf temperature=%lf \n", v, t);
}

void adc_setup()
{
    adc1_config_width(ADC_WIDTH_BIT_12);                       //adc1  数据长度 12 bit
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_0db);  //通道0，满量程1.1V
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_0db);  //通道3，满量程1.1v
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_11db); //通道6，满量程3.9V
}

void adc_loop()
{
    get_light();
    get_temperature();
    delay(1000);
}

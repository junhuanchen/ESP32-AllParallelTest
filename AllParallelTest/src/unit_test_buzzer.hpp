#include <Arduino.h>

#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_13_BIT 13

#define brightness 5
#define BuzzerPin 25

#define BottomB 27

static void buzzer_ledc_AnalogWrite(uint8_t channel, uint32_t value)
{
    // calculate duty, 8191 from 2 ^ 13 - 1 (2 ^ LEDC_TIMER_13_BIT - 1)
    // value_MAX = 255
    uint32_t duty = (8191 / 255) * value;
    // write duty to LEDC
    ledcWrite(channel, duty);
}

void buzzer_setup()
{
    ledcSetup(LEDC_CHANNEL_0, 0, LEDC_TIMER_13_BIT);
    ledcAttachPin(BuzzerPin, LEDC_CHANNEL_0);
    pinMode(BottomB, INPUT);
}

void buzzer_loop()
{
    delay(500);

    static enum Buzzer {
        Idle,
        Write,
        Clear,
    } State = Buzzer::Idle;

    switch (State)
    {
    case Idle:
        // if (digitalRead(BottomB) == LOW)
        {
            printf("buzzer_Start\n");
            State = Write;
        }
        break;
    case Write:
        static int BuzzerledcBaseFreq = 280;
        BuzzerledcBaseFreq = BuzzerledcBaseFreq + 20;
        if (BuzzerledcBaseFreq > 560)
            BuzzerledcBaseFreq = 280;

        ledcWriteTone(LEDC_CHANNEL_0, BuzzerledcBaseFreq);
        // set the brightness on LEDC channel 0
        buzzer_ledc_AnalogWrite(LEDC_CHANNEL_0, brightness);
        printf("buzzer_Write Freq:%d Duty:%lf \n", BuzzerledcBaseFreq, brightness / 2.55);
        State = Clear;
        break;
    case Clear:
        buzzer_ledc_AnalogWrite(LEDC_CHANNEL_0, 0);
        printf("buzzer_Clear\n");
        State = Idle;
        break;
    }
}

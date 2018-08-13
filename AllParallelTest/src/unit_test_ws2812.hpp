//BIT NEW
//BPI - BIT test code
#include <Arduino.h>
#include <NeoPixelBus.h>

const uint16_t PixelCount = 25;
const uint8_t PixelPin = 4;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

#define ledPower 2
#define BottomA 35

int brightness = 0;
int fadeAmount = 5;

void ws2812_setup()
{
    pinMode(BottomA, INPUT);
    pinMode(ledPower, OUTPUT);
}

void ws2812_loop()
{
    delay(1000);

    static enum Ws2812 {
        Idle,
        Write,
        Clear,
    } State = Ws2812::Idle;

    switch (State)
    {
    case Idle:
        // if (digitalRead(BottomA) == LOW)
        {
            digitalWrite(ledPower, HIGH);
            strip.Begin();
            State = Write;
            printf("ws2812_Start\n");
        }
        break;
    case Write:
    {
        RgbColor ColorS[] = {RgbColor(0, 0, 1), RgbColor(0, 1, 1), RgbColor(1, 1, 1), RgbColor(1, 1, 0), RgbColor(1, 0, 0), RgbColor(0, 1, 0), RgbColor(1, 0, 1) };
        static uint8_t ColorsI = 0;

        if (ColorsI > 7)
            ColorsI = 0;

        for (int i = 0; i < 100; i += 20)
        {
            if (ColorS[ColorsI].R > 0)
                ColorS[ColorsI].R += 20;
            if (ColorS[ColorsI].G > 0)
                ColorS[ColorsI].G += 20;
            if (ColorS[ColorsI].B > 0)
                ColorS[ColorsI].B += 20;
            for (int i = 0; i < strip.PixelCount(); i++)
                strip.SetPixelColor(i, ColorS[ColorsI]);
            strip.Show();
            delay(50);
        }

        for (int i = 0; i < 100; i += 20)
        {
            if (ColorS[ColorsI].R > 0)
                ColorS[ColorsI].R -= 20;
            if (ColorS[ColorsI].G > 0)
                ColorS[ColorsI].G -= 20;
            if (ColorS[ColorsI].B > 0)
                ColorS[ColorsI].B -= 20;
            for (int i = 0; i < strip.PixelCount(); i++)
                strip.SetPixelColor(i, ColorS[ColorsI]);
            strip.Show();
            delay(50);
        }

        ColorsI += 1;
        State = Clear;
        printf("ws2812_Write\n");
        break;
    }
    case Clear:
        digitalWrite(ledPower, LOW);
        State = Idle;
        printf("ws2812_Clear\n");
        break;
    }
}
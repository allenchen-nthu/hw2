// uLCD-144-G2 basic text demo program for uLCD-4GL LCD driver library
//
#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
DigitalIn plu(D3);
DigitalIn sele(D6);
DigitalIn minu(D5);
AnalogOut pwr(D13);
AnalogOut aout(D7);
AnalogIn Ain(A0);

int main()
{
    // basic printf demo = 16 by 18 characters on screen
    uLCD.background_color(0x0);
    uLCD.textbackground_color(0x0);
    uLCD.cls();
    uLCD.color(BLUE);
    uLCD.printf("\n select frequency\n"); //Default Green on black text
    uLCD.color(GREEN);
    uLCD.printf("\n1Hz         1000Hz\n"); //Default Green on black text
    //uLCD.printf("\n  Starting Demo...");
    uLCD.text_width(2); //4X size text
    uLCD.text_height(2);
    uLCD.color(GREEN);
    int scale = 1;
    int aval = 1;
    int sample = 128;
    int j;
    float ADCdata[128];
    while(1) {
        aout = 0;
        pwr = 1;
        uLCD.locate(0,3);
        if (scale != 7 &&  plu.read() == 1 && aval == 1)
        {
            ThisThread::sleep_for(500ms);
            scale++;
        }
        if (scale != 1 && minu.read() == 1 && aval == 1)
        {
            ThisThread::sleep_for(500ms);
            scale--;
        }
        if (scale == 1)
        {
            uLCD.printf(" +       ");
            if (sele.read() == 1)
            {
                aval = !aval;
                ThisThread::sleep_for(500ms);
            }
        }
        if (scale == 2)
        {
            uLCD.printf(" ++      ");
            if (sele.read() == 1)
            {
                aval = !aval;
                ThisThread::sleep_for(500ms);  
            }
        }
        if (scale == 3)
        {
            uLCD.printf(" +++     ");
            if (sele.read() == 1)
            {
                aval = !aval;
                ThisThread::sleep_for(500ms);   
            }
        }
        if (scale == 4)
        {
            uLCD.printf(" ++++    ");
            if (sele.read() == 1)
            {
                aval = !aval;
                ThisThread::sleep_for(500ms);
            }
        }
        if (scale == 5)
        {
            uLCD.printf(" +++++   ");
            if (sele.read() == 1)
            {
                aval = !aval;
                ThisThread::sleep_for(500ms);
            }
        }
        if (scale == 6)
        {
            uLCD.printf(" ++++++  ");
            if (sele.read() == 1)
            {
                aval = !aval;
                ThisThread::sleep_for(500ms);
            }
        }
        if (scale == 7)
        {
            uLCD.printf(" +++++++ ");
            if (sele.read() == 1)
            {
                aval = !aval;
                ThisThread::sleep_for(500ms);
            }
        }

        if (aval == 0){
            uLCD.color(RED);
            for (float i = 0.0f; i < 1.0f; i += 0.1f) {
                if (i <= 0.2f){
                    aout = 5.0f * i;
                } else {
                    aout = (1.0f - ((i - 0.2f) / 0.8f));
                }
                    //printf("aout = %f volts\n", aout.read() * 3.0f);
                if (scale == 1) ThisThread::sleep_for(1s);
                if (scale == 2) ThisThread::sleep_for(300ms);
                if (scale == 3) ThisThread::sleep_for(100ms);
                if (scale == 4) ThisThread::sleep_for(30ms);
                if (scale == 5) ThisThread::sleep_for(10ms);
                if (scale == 6) ThisThread::sleep_for(3ms);
                if (scale == 7) ThisThread::sleep_for(1ms);
            } 
        } else {
                uLCD.color(GREEN);
        }
        for (j = 0; j < sample; j++){
            aout = Ain;
            ADCdata[j] = Ain;
            ThisThread::sleep_for(1000ms/sample);
        }
        for (j = 0; j < sample; j++){
            printf("%f\r\n", ADCdata[j]);
            ThisThread::sleep_for(100ms);
        }
    }
}

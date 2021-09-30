#include "mbed.h"
#include "tsi_lib.h"

/* This defines will be replaced by PinNames soon */
#define ELEC0 9
#define ELEC1 10

int main(void) {
    PwmOut led(LED_GREEN);
    TSIAnalogSlider tsi(ELEC0, ELEC1, 40);
    
    while (true) {
        led = 1.0 - tsi.readPercentage();
        wait(0.1);
    }
}


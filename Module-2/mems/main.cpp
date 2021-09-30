/**
 * @file main.cpp
 * @author Sankalp Agrawal (saag2511@colorado.edu)
 *         Ayush Gupta (aygu7370@colorado.edu)
 * @brief File for initializing and driving the accelerometer
 * @version 0.1
 * @date 2021-29-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "mbed.h"
#include "MMA.h"

#define SDA PTE25
#define SCL PTE24

Serial pc(USBTX, USBRX); // tx, rx
/**
 * @brief Main routine used for initialization and driving the
 *        code. This routine is doing the following
 *        - Initilizing i2c
 *        - reading accelerometer
 *        - driving the LED
 * 
 * @return return 1
 */
int main()
{
    pc.printf("Starting...\r\n");
    MMA mems(SDA, SCL, (0x1D<<1)); // Initialise
    mems.wakeup(); // wakeup the sensor
    wait(1);
    uint8_t val = mems.who_am_i(); // read the device identifier
    pc.printf("who_am_i() : 0x%02X\r\n", val);
    float val_val[3] = {0.00, 0.00, 0.00};
    PwmOut rled(LED1);
    PwmOut gled(LED2);
    PwmOut bled(LED3);
    
    while(1) {  
        mems.readData(val_val,3);
        rled = val_val[0];
        gled = val_val[1];
        bled = val_val[2];
        wait(0.2);
        wait(0.4);
    }
}

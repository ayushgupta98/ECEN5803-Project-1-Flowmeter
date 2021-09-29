#include "mbed.h"
#include "MMA.h"

#define SDA PTE25
#define SCL PTE24

Serial pc(USBTX, USBRX); // tx, rx

int main()
{
    //char arr[100];
    pc.printf("Starting...\r\n");
    MMA mems(SDA, SCL, (0x1D<<1));
    mems.wakeup();
    wait(1);
    uint8_t val = mems.who_am_i();
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
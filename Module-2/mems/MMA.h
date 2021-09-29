#ifndef _MMA_H_
#define _MMA_H_

#include "mbed.h"

class MMA
{
    private:
        enum{
            eWhoAmIOpcode = 0x0D,
            eOutXmsb = 0x01,
            eOutXlsb = 0x02,
            eOutYmsb = 0x03,
            eOutYlsb = 0x04,
            eOutZmsb = 0x05,
            eOutZlsb = 0x06,
            eCtrlReg1 = 0x2A,
            eCtrlReg2 = 0x2B,
            eCtrlReg3 = 0x2C,
            eCtrlReg4 = 0x2D,
            eCtrlReg5 = 0x2E,
        };
    public:
        MMA(PinName sda, PinName scl, uint8_t dev_addr);
        ~MMA();
        void initSequence();
        void sendData(char* data, uint16_t num_bytes);
        void readData(char* data, uint16_t num_bytes);
        void readData(float* data, uint16_t num_bytes);
        uint8_t who_am_i();
        static void interrupt_1_isr();
        static void interrupt_2_isr();
        void wakeup();
    private:
        Serial pc; // tx, rx
        I2C cnf;
        uint8_t devAaddr;
};

#endif
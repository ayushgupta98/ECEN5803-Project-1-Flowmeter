#include "MMA.h"

/**
 * The slave address of the device is 0x1D
 */

        
MMA::MMA(PinName sda, PinName scl, uint8_t dev_addr) : pc(USBTX, USBRX), cnf(sda, scl),\
devAaddr(dev_addr)
{
    /*
    InterruptIn interrupt_1_mms(PTA14);
    InterruptIn interrupt_2_mms(PTA15);
 
    interrupt_1_mms.mode(PullUp);
    interrupt_1_mms.rise(interrupt_1_isr);
    interrupt_2_mms.mode(PullUp);
    interrupt_2_mms.rise(interrupt_2_isr);*/
}
MMA::~MMA()
{
}
void MMA::initSequence()
{
}
void MMA::interrupt_1_isr()
{
}
void MMA::interrupt_2_isr()
{
}
uint8_t MMA::who_am_i()
{
    char byte[1] = {eWhoAmIOpcode};
    cnf.write(devAaddr, byte, 1, true);
    sendData(byte, sizeof(byte)/sizeof(byte[0]));
    
    uint8_t regVal;
    readData((char*)&regVal, 1);
    return regVal;
}
void MMA::wakeup()
{
    char byte[2] = {eCtrlReg1, 0x01}; // Low noise mode and active mode.
    sendData(byte, sizeof(byte)/sizeof(byte[0]));
}
void MMA::readData(float* data, uint16_t num_bytes)
{
    char byte[1] = {eOutXmsb};
    cnf.write(devAaddr, byte, sizeof(byte)/sizeof(byte[0]), true);
    sendData(byte, sizeof(byte)/sizeof(byte[0]));
    int16_t x = 0, y = 0, z = 0;
    uint8_t val[6] = {0, 0, 0, 0, 0, 0};
    readData((char*)&val, 6);
    // x_val[0] will contain the first byte of numbers x13-x6
    // x_val[1] will contain the second byte of numbers x5-x0
    // since in the memory x_val is stored as x[1]x[0],
    // we need to do the following to get the proper x value: x[0] << 6 | x[1] >> 2
    
    // No negative values
    if(val[0] > 0x7F)
    {
        val[0] -= 0x7F;
    }
    if(val[2] > 0x7F)
    {
        val[2] -= 0x7F;
    }
    if(val[4] > 0x7F)
    {
        val[4] -= 0x7F;
    }
    x = (val[0] << 6 | val[1] >> 2);
    y = (val[2] << 6 | val[3] >> 2);
    z = (val[4] << 6 | val[5] >> 2);
    float final_x_val = x/4096.0;
    float final_y_val = y/4096.0;
    float final_z_val = z/4096.0;
    data[0] = final_x_val;
    data[1] = final_y_val;
    data[2] = final_z_val;
    pc.printf("%f %f %f\r\n", final_x_val, final_y_val, final_z_val);
}
void MMA::sendData(char* data, uint16_t num_bytes)
{
    cnf.write(devAaddr, data, num_bytes, true);
}
void MMA::readData(char* data, uint16_t num_bytes)
{
    cnf.read(devAaddr, data, num_bytes, true);
}
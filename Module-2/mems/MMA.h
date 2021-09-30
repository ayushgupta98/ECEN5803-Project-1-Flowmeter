/**
 * @file MMA.h
 * @author Sankalp Agrawal (saag2511@colorado.edu)
 *         Ayush Gupta (aygu7370@colorado.edu)
 * @brief Interface for the user to drive the on board 
 *        accelerometer.
 * @version 0.1
 * @date 2021-29-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
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
				/**
				 * @brief Constructor for initialising the i2c accelerometer
				 * 
				 * @param sda       I2C Serial Data Pin
				 * @param scl       I2C Serial Clock Pin
				 * @param dev_addr  I2C device address
				 */
        MMA(PinName sda, PinName scl, uint8_t dev_addr);
			  /**
				 * @brief Destructor for the class
		     */
        ~MMA();
		    /**
				 * @brief Constructor for initialising the i2c accelerometer
				 * 
				 * @param data       Data to send to the device
				 * @param num_bytes  Number of bytes to send
				 */
        void sendData(char* data, uint16_t num_bytes);
		    /**
				 * @brief Function to read the x,y and z values.
				 * 
				 * @param data       Float array in which the x,y and z values willl be stored.
				 * @param num_bytes  Array size
				 */
        void readData(float* data, uint16_t num_bytes);
				/**
				 * @brief Function to read the device identifier
				 *
				 * @return uint8_t identifier of the i2c device
				 */
        uint8_t who_am_i();
				/**
				 * @brief Waking up the I2C device.
				 */
        void wakeup();
				uint8_t devAaddr;
		    /**
				 * @brief Function to read the x, y and z values.
				 * 
				 * @param data       Data array in which the data read from the i2c device will
		     *                   be stored.
				 * @param num_bytes  Number of bytes to be stored in the array
				 */
			  void readData(char* data, uint16_t num_bytes);
    private:
        Serial m_pc; // tx, rx
        I2C m_cnf;
};

#endif

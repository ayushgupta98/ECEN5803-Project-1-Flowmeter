/**
 * @file adc.h
 * @author Sankalp Agrawal (saag2511@colorado.edu)
 *         Ayush Gupta (aygu7370@colorado.edu)
 * @brief ADC helper fucntions
 * @version 0.1
 * @date 2021-29-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _ADC_H_
#define _ADC_H_
/**
 * @brief Initializes the ADC and sets the appropriate registers.
 * 		  Thia ADC is NOT a Interrupt based ADC, instead it is a polling based
 *        ADC.
 * 
 * @return unsigned 1, if initialized and calibrated
 *                  0, otherwise
 */
unsigned char Adc_Init();

/**
 * @brief This function takes the input from the user about which
 *        channel they want to get the ADC readings from. This function
 *        reads the ADC value of that channel and returns it to the user.
 *
 * @param channel From which the ADC values are read
 * 
 * @return unsigned short ADC samples are read and returned
 */
unsigned short Adc_ReadMesaurement(unsigned char channel);

#endif

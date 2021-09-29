#ifndef _ADC_H_
#define _ADC_H_
/*
 * @brief Initializes the ADC and sets the appropriate registers.
 * Thia ADC is NOT a Interrupt based ADC, instead it is a polling based
 * ADC.
 * 
 * Returns:
 *   unsigned 1, if initialized and calibrated
 *            0, otherwise
 */
unsigned char Adc_Init();

/*
 * @brief This function takes the input from the user about which
 * channel they want to get the ADC readings from. This function
 * reads the ADC value of that channel and returns it to the user.
 *
 * Parameters:
 *   channel From which the ADC values are read
 * 
 * Returns:
 *   unsigned short ADC samples are read and returned
 */
unsigned short Adc_ReadMesaurement(unsigned char channel);

#endif

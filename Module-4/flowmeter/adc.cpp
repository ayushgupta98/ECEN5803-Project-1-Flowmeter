/**
 * @file adc.cpp
 * @author Sankalp Agrawal (saag2511@colorado.edu)
 *         Ayush Gupta (aygu7370@colorado.edu)
 * @brief functions defined in the corresponding h file are populated here
 * @version 0.1
 * @date 2021-29-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "shared.h"
#include "adc.h"

unsigned char Adc_StartCalibration()
{
	// Enable calibration sequence
	ADC0->SC3 = ADC_SC3_CAL_MASK;
	// Capture the ADC value
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}
	// Perform actual calibration as mentioned in the datasheet
	unsigned short calib_val = 0;
	calib_val = ADC0->CLP0 + ADC0->CLP1 + ADC0->CLP2 + ADC0->CLP3 + ADC0->CLP4 + ADC0->CLPS;
	calib_val = calib_val/2;
	calib_val |= 1 << 15;
	ADC0->PG = calib_val;
		
	calib_val = 0;
	calib_val = ADC0->CLM0 + ADC0->CLM1 + ADC0->CLM2 + ADC0->CLM3 + ADC0->CLM4 + ADC0->CLMS;
	calib_val = calib_val/2;
	calib_val |= 1 << 15;
	ADC0->MG = calib_val;
		
	// Return value indicating whether the claibration passed or failed.
	return((ADC0->SC3 & ADC_SC3_CALF_MASK) >> ADC_SC3_CALF_SHIFT);
}

unsigned char Adc_Init()
{
	// Enable clock on PORTB
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	// Enable clock on ADC0
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	// Set Channel 1 to be analog
	PORTB->PCR[1] = PORT_PCR_MUX(0);
	// Software trigger
	ADC0->SC2 &= ~(ADC_SC2_ADTRG_MASK);
	// Reference voltage selection, by defualt it is Vrefh and Vrefl
	ADC0->SC2 |= ADC_SC2_REFSEL(0);
	// Enable hardware averaging function
	ADC0->SC3 |= ADC_SC3_AVGS(3);
	// Normal power mode, by default 8bit resolution
	ADC0->CFG1 &= ~ADC_CFG1_ADLPC_MASK | ~ADC_CFG1_MODE_MASK;
	// Input clock is divided by 1, Long sampling period
	ADC0->CFG1 |= ADC_CFG1_ADIV(0) | (1 << ADC_CFG1_ADLSMP_MASK); 
	UART_direct_msg_put("Calibration result : ");
	// Begin calibration
	unsigned char ret_val = Adc_StartCalibration();
	UART_direct_msg_put((ret_val) ? "Fail\r\n" : "Passed\r\n");
	// Return if the calibration succeeded
	return ret_val;
}

unsigned short Adc_ReadMesaurement(unsigned char channel)
{
	// Clear the channel bits
	ADC0->SC1[0] &= ~(ADC_SC1_ADCH_MASK);
	switch(channel)
	{
		// In case of channel 30, Reference voltage
		case CHANNEL_0:
		{
			// Set resolution to 8 bit mode
			ADC0->CFG1 |= ADC_CFG1_MODE(0);
			// No continuous conversion, disable hardware averageing
			ADC0->SC3 &= ~(1 << ADC_SC3_ADCO_SHIFT) | ~(1 << ADC_SC3_AVGE_SHIFT);
			// Set the ADC capture channel
			ADC0->SC1[0] |= ADC_SC1_ADCH(0x1E); // VREFL
		}
		break;
		// In case of channel 9, Analog In on A1
		case CHANNEL_1:
		{
			// Set resolution to 16 bit mode
			ADC0->CFG1 |= ADC_CFG1_MODE(3);
			// Continuous conversion, Eable hardware averageing
			ADC0->SC3 |= (1 << ADC_SC3_ADCO_SHIFT) | (1 << ADC_SC3_AVGE_SHIFT);
			// Set the ADC capture channel
			ADC0->SC1[0] |= ADC_SC1_ADCH(0x09); // analog_d1
		}
		break;
		// In case of channel 26, Temperature sensor
		case CHANNEL_2:
		{
			// Set resolution to 16 bit mode
			ADC0->CFG1 |= ADC_CFG1_MODE(3);
			// Continuous conversion, Eable hardware averageing
			ADC0->SC3 |= (1 << ADC_SC3_ADCO_SHIFT) | (1 << ADC_SC3_AVGE_MASK);
			// Set the ADC capture channel
			ADC0->SC1[0] |= ADC_SC1_ADCH(0x1A); // temp sensor
		}
		break;
	};
	
	//while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}
	// Return the ADC value
	return ADC0->R[0];
}

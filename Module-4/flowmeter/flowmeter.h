/**
 * @file flowmeter.h
 * @author Sankalp Agrawal (saag2511@colorado.edu)
 *         Ayush Gupta (aygu7370@colorado.edu)
 * @brief Interface Functions for Flowmeter computation
 * @version 0.1
 * @date 2021-29-10
 * 
 * @copyright Copyright (c) 2021
 * 
 *
 */
#ifndef _FLOWMETER_H_
#define _FLOWMETER_H_

/**
 * @brief This function calculates the frequency of the raw ADC samples
 * from the vortex flow meter. 
 * 
 * @param samples       ADC sample buffer
 * @param nsamples      Number of samples in the buffer
 * @param sampling_time Sampling time of the ADC in microseconds
 * @param noise_factor  estimated noise
 * 
 * @return float Computed frequnecy in Hertz
 */
float frequency_detection(unsigned int samples[], unsigned int nsamples, unsigned int sampling_time, unsigned char noise_factor);

/**
 * @brief This function takes in frequency and temperature in reat time 
 * and computes the flow rate of the material through the vortex meter
 *
 * @param freq      Frequency from the fortex flow meter sensor in Hetz
 * @param adc_temp  Real time temperature in ADC raw values
 * 
 * Returns:
 *   float flowrate in gallons/minute
 */
float calculateFlow(unsigned int freq, unsigned short adc_temp);

#endif

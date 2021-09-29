#ifndef _FLOWMETER_H_
#define _FLOWMETER_H_

/*
 * @brief This function calculates the frequency of the raw ADC samples
 * from the vortex flow meter. 
 *
 * Parameters:
 *   samples       ADC sample buffer
 *   nsamples      Number of samples in the buffer
 *   sampling_time Sampling time of the ADC in microseconds
 *   noise_factor  estimated noise
 * 
 * Returns:
 *   float Computed frequnecy in Hertz
 */
float frequency_detection(unsigned int samples[], unsigned int nsamples, unsigned int sampling_time, unsigned char noise_factor);

/*
 * @brief This function takes in frequency and temperature in reat time 
 * and computes the flow rate of the material through the vortex meter
 *
 * Parameters:
 *   freq      Frequency from the fortex flow meter sensor in Hetz
 *   adc_temp  Real time temperature in ADC raw values
 * 
 * Returns:
 *   float flowrate in gallons/minute
 */
float calculateFlow(unsigned int freq, unsigned short adc_temp);

#endif

#ifndef _FLOWMETER_H_
#define _FLOWMETER_H_

float frequency_detection(unsigned int samples[], unsigned int nsamples, unsigned int sampling_time, unsigned char noise_factor);
float calculateFlow(unsigned int freq, unsigned short adc_temp);

#endif

/**
 * @file flowmeter.cpp
 * @author Sankalp Agrawal (saag2511@colorado.edu)
 *         Ayush Gupta (aygu7370@colorado.edu)
 * @brief Flowmeter computation
 * @version 0.1
 * @date 2021-29-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "shared.h"
#include <stdint.h>
#include <math.h>
#include "adc.h"

#define PID 0.07366f // Pipe Inner Diameter in meters
#define d 0.0127f // Pipe width in meters


/*
 * @brief ADC sampling and flow calculation are expensive
 * and hence we need a mechanism that does both with low latency
 * and for this we've implemented a ping-pong buffer mechniasm 
 * for capturing and computing.
 * 
 * Ping Pong buffer:
 * Two buffer are employed in this approach. One is a ping buffer
 * and the other is a pong buffer. This method works because we have
 * two processes that we want done. When the ADC interrupt readings
 * are filling the ping buffer, we can compute the flow using the pong
 * buffer. As soon as the flow calculation is complete, the roles are 
 * and now we perform flow calculation on the ping buffer while the ADC 
 * fills the pong buffer.
 */

uint16_t buffer_1[ADC_BUF_SIZE];
volatile uint8_t isBuf_1_full = 0;
volatile uint8_t process_buf_1 = 0;

uint16_t buffer_2[ADC_BUF_SIZE];
volatile uint8_t isBuf_2_full = 1;
volatile uint8_t process_buf_2 = 1;
float temp = 0;

void ADC_Buffer_Sample(uint8_t channel)
{
	if(isBuf_2_full)
	{
		static uint16_t buf_1_cntr = 0;
		buffer_1[buf_1_cntr++] = Adc_ReadMesaurement(channel);
		if(buf_1_cntr >= ADC_BUF_SIZE) { 
			isBuf_2_full = 0; 
			isBuf_1_full = 1;
			process_buf_1 = 1;			
			buf_1_cntr = 0; 
		} 
	}
	else if(isBuf_1_full)
	{
		static uint16_t buf_2_cntr = 0;
		buffer_2[buf_2_cntr++] = Adc_ReadMesaurement(channel);
		if(buf_2_cntr >= ADC_BUF_SIZE) { 
			isBuf_2_full = 1;
			isBuf_1_full = 0;
			process_buf_2 = 1;					
		  buf_2_cntr = 0; 
		} 
	}
}
float frequency_detection(uint16_t samples[], uint32_t nsamples, uint32_t sampling_time, uint8_t noise_factor){
    uint32_t ntransitions = 0;
    uint32_t nsamples_passed = 0;
    uint8_t min_flag = 0;
    uint8_t max_flag = 0;
    uint8_t is_counting = 0;
    uint32_t prev_sample_reading_taken = 0;
    uint32_t i = 0;
    float frequency = 0.0f;
    for (i = 1; i<nsamples; i++) { //i = 2:nsamples
        if ((samples[i] - samples[i-1]) >= noise_factor){
            if (max_flag){
                max_flag = 0;
                if (is_counting){
                    ntransitions = ntransitions + 1;
                    nsamples_passed = nsamples_passed + i - prev_sample_reading_taken;
                    prev_sample_reading_taken = i;
                }
                else{
                    prev_sample_reading_taken = i;
                    is_counting = 1;
                }
            }
            min_flag = 1;
        }
        else if ((samples[i-1] - samples[i]) >= noise_factor){
            if (min_flag){
                min_flag = 0;
                if (is_counting){
                    ntransitions = ntransitions + 1;
                    nsamples_passed = nsamples_passed + i - prev_sample_reading_taken;
                    prev_sample_reading_taken = i;
                }
                else{
                    prev_sample_reading_taken = i;
                    is_counting = 1;
                }
            }
            max_flag = 1;
        }

    if (ntransitions == 0) {
        frequency = 100.0f;
    }  
    else{
        frequency = (1000000.0f/((nsamples_passed/ntransitions) * sampling_time * 2.0f));
    }
    return frequency;
	}
}

float calculateFlow(uint32_t freq, uint16_t adc_temp)
{
#if 0
	if(process_buf_2)
	{
		freq = frequencyDetection(buffer_2, 100, 0.0001);
		process_buf_2 = 0;
	}
	else if(process_buf_1)
	{
		freq = frequencyDetection(buffer_1, 100, 0.0001);
		process_buf_1 = 0;
	}
	else
	{
		return;
	}
#endif
#if 0
	// Get temperature in volt
	float v_temp = adc_temp*0.0029296875;
	// Recognise the m factor
	float m = (v_temp > 0.7012f) ? 0.001646f : 0.001749f;
	// calculate thempertaure in kelvin

	temp = (25.0f - ((v_temp - 0.7012f)/m));
#else
	temp = adc_temp;
#endif
	// Calculate the viscosity. T is in kelvin
	float viscosity = 2.4f * 0.00001f * pow(10.0f, 247.8f / (temp + 273.15f - 140.0f));
	// Calculate the viscosity. T is in Celcius
  float density =  (1000.0f - (((temp*1000.0f) + 288941.4f))/ ((508929.2f *temp )+ 34673158.092196f) * pow(temp - 3.9863f, 2.0f));
	// equations lead to a quadratic formula for which the a, b and c are as follows
	float a = 0.0671708648f;
  float b = -1.0f*((0.5005280534f*freq*d) + (viscosity / (density*PID)));
  float c = 0.9324293096f*pow((freq*d), 2);
	// Real part of the quadratic formula
  float res_1 = (-b/(2.0f*a));
	// Imaginary part of the quadratic formula
  float res_2 = sqrt(((b*b) - (4.0f*a*c)))/(2.0f*a);
	// Polar form conversion
  float vel = res_1 + res_2;
	// Return the flow in gallons per feet
	return( 2.45f*2.9f*2.9f*vel*3.28f);
}
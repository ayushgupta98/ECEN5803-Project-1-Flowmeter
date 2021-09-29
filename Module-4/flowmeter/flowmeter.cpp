#include "shared.h"
#include <stdint.h>
#include <math.h>
#include "adc.h"
#define PID 0.07366f
#define d 0.0127f
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
	/*
	if(process_buf_2)
	{
		frequency = frequencyDetection(buffer_2, 100, 0.0001);
		process_buf_2 = 0;
	}
	else if(process_buf_1)
	{
		frequency = frequencyDetection(buffer_1, 100, 0.0001);
		process_buf_1 = 0;
	}
	else
	{
		return;
	}*/
	//volt = ((adc_temp/65536)*3.3)
	float v_temp = adc_temp*0.00004578f;
	float m = (v_temp > 0.716f) ? 0.001646f : 0.001769f;
	temp = (25.0f - ((v_temp - 0.716f)/m)) + 274.15f; // 152 bytes
	float viscosity = 2.4f * 0.00001f * pow(10.0f, 247.8f / (temp + 273.15f - 140.0f)); // t is in kelvin // 68 bytes
  float density =  (1000.0f - (((temp*1000.0f) + 288941.4f))/ ((508929.2f *temp )+ 34673158.092196f) * pow(temp - 3.9863f, 2.0f)); // 116 bytes
	float a = 0.0671f;
  float b = -1.0f*((0.05368f*freq*d) + (viscosity / (density*PID))); //260 bytes
  float c = pow((freq*d), 2); // 88 bytes
  float res_1 = (-b/(2.0f*a));
  float res_2 = sqrt(-1.0f*((b*b) - (4.0f*a*c)))/(2.0f*a);
  float vel = sqrt((res_1*res_1) + (res_2*res_2));
	
	return( 2.45f*2.9f*2.9f*vel*3.28f);
}
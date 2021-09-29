#include "shared.h"
#include "adc.h"

unsigned char Adc_StartCalibration()
{
	ADC0->SC3 = ADC_SC3_CAL_MASK;
	
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}
	
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
	return((ADC0->SC3 & ADC_SC3_CALF_MASK) >> ADC_SC3_CALF_SHIFT);
}

unsigned char Adc_Init()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	
	PORTB->PCR[0] = PORT_PCR_MUX(0);
	//PORTB->PCR[1] = PORT_PCR_MUX(0);
	PORTB->PCR[2] = PORT_PCR_MUX(0);
	ADC0->SC2 &= ~(ADC_SC2_ADTRG_MASK);
	ADC0->SC2 |= ADC_SC2_REFSEL(0);
	ADC0->SC3 |= ADC_SC3_AVGS(32);
	ADC0->CFG1 &= ~ADC_CFG1_ADLPC_MASK | ~ADC_CFG1_MODE_MASK;
	ADC0->CFG1 |= ADC_CFG1_ADIV(0) | (1 << ADC_CFG1_ADLSMP_MASK); 
	//UART_direct_msg_put("Calibration result : ");
	unsigned char ret_val = Adc_StartCalibration();
	//UART_direct_msg_put((ret_val) ? "Fail\r\n" : "Passed\r\n");
	//ADC0->SC1[0] |= ADC_SC1_AIEN_MASK;
	
	return ret_val;
}

unsigned short Adc_ReadMesaurement(unsigned char channel)
{
	ADC0->SC1[0] &= ~(ADC_SC1_ADCH_MASK);
	switch(channel)
	{
		case CHANNEL_0:
		{
			ADC0->CFG1 |= ADC_CFG1_MODE(0);
			ADC0->SC3 &= ~(1 << ADC_SC3_ADCO_SHIFT) | ~(1 << ADC_SC3_AVGE_MASK);
			ADC0->SC1[0] |= ADC_SC1_ADCH(0x1E); // VREFL
		}
		break;
		case CHANNEL_1:
		{
			ADC0->CFG1 |= ADC_CFG1_MODE(3);
			ADC0->SC3 |= (1 << ADC_SC3_ADCO_SHIFT) | (1 << ADC_SC3_AVGE_MASK);
			ADC0->SC1[0] |= ADC_SC1_ADCH(0x09); // analog_d1
		}
		break;
		case CHANNEL_2:
		{
			ADC0->SC1[0] &= ~(ADC_SC1_ADCH_MASK);
			ADC0->CFG1 |= ADC_CFG1_MODE(3);
			ADC0->SC3 |= (1 << ADC_SC3_ADCO_SHIFT) | (1 << ADC_SC3_AVGE_MASK);
			ADC0->SC1[0] |= ADC_SC1_ADCH(0x1A); // temp sensor
		}
		break;
	};
	
	//while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)){}
	return ADC0->R[0];
}

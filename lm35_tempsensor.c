 /*
 * lm35_tempsensor.c
 *
 *  Created on: ???/???/????
 *      Author: Omar
 */
 
#include <util/delay.h> /* For the delay functions */
#include "lm35_tempsensor.h"
#include "adc.h"


/*
 * Description :               
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_readTemperature(Channel_Selection channel)
{
	uint8 tempValue = 0;
	uint16 adcRead = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adcRead = ADC_polling_readChannel(channel);

	/* Make delay for some time until ADC read process is done */
	_delay_ms(10);

	/* Calculate the temperature from the ADC value*/
	tempValue = (uint8) ( ((uint32) adcRead * SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) / (ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE) );

	return tempValue;
}

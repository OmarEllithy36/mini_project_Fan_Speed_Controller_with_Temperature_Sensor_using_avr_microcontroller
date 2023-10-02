 /*
 * lm35_tempsensor.h
 *
 *  Created on: ???/???/????
 *      Author: Omar
 */

#ifndef LM35_TEMPSENSOR_H_
#define LM35_TEMPSENSOR_H_

#include "data_types.h"
#include "adc.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_readTemperature(Channel_Selection channel);

#endif /* LM35_TEMPSENSOR_H_ */

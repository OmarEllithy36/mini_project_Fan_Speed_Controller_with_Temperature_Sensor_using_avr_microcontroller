/*
 * ADC.h
 *
 *  Created on: ???/???/????
 *      Author: Omar
 */

#ifndef ADC_H_
#define ADC_H_

#include "data_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * ADC Configuration for Enable or Disable Auto Trigger mode
 * Write LOGIC_HIGH To Enable & LOGIC_LOW To Disable
 */
#define AUTO_TRIGGER_ENABLE   LOGIC_LOW

/*
 * 	Configuration of Polling & Interrupt Mode
 * 	Write TRUE for using interrupt design
 */
#define INT_MODE	FALSE

/*
 * Configure of ADC reference voltage value
 * Configure of ADC maximum bit value
*/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by other modules */

#if(INT_MODE == TRUE)
extern volatile uint16 g_ADCreturn;
#endif

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	MAX_VOLTAGE_5V,SPESIFIC_VOLTAGE,INTERNAL_VLOTAGE = 3
}Voltage_RF;

typedef enum
{
	ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7
}Channel_Selection;

typedef enum
{
	FACTOR_2 =1,FACTOR_4,FACTOR_8,FACTOR_16,FACTOR_32,FACTOR_64,FACTOR_128
}PRESCALER_SELECT;

#if(AUTO_TRIGGER_ENABLE == LOGIC_HIGH)
typedef enum
{
	FREE_RUNNING,ANALOG_COMPARATOR,EXTERNAL_INTERRUPT_REQUEST_0,TIMER_COUNTER0_COMPARE_MATCH,\
	TIMER_COUNTER0_OVERFLOW,TIMER_COUNTER1_COMPARE_MATCH_B,TIMER_COUNTER1_OVERFLOW,\
	TIMER_COUNTER1_CAPTURE_EVENT
}Auto_Trigger_Mode;
#endif

typedef struct
{
	Voltage_RF V_RF;
	Channel_Selection channel;
	PRESCALER_SELECT prescaler;
#if(AUTO_TRIGGER_ENABLE == LOGIC_HIGH)
	Auto_Trigger_Mode trigger;
#endif

}ADC_Config;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_Config *config_ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and with "POLLING TECHNIQUE" convert it to digital using the ADC driver.
 */
uint16 ADC_polling_readChannel(Channel_Selection channel);

#if(INT_MODE == TRUE)
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and with "INTERRUPT DESIGN" convert it to digital using the ADC driver.
 */
void ADC_INT_readChannel(Channel_Selection channel);
#endif

#endif /* ADC_H_ */

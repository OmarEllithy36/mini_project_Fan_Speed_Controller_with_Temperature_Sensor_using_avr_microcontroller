/*
 * ADC.c
 *
 *  Created on: ???/???/????
 *      Author: Omar
 */
#include "ADC.h"
#include "bit_math.h"
#include <avr/io.h>

#if(INT_MODE == TRUE)
#include <avr/interrupt.h>
#endif

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
#if(INT_MODE == TRUE)
volatile uint16 g_ADCreturn = 0;
#endif
/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
#if(INT_MODE == TRUE)
ISR(ADC_vect)
{
	g_ADCreturn = ADC;
}
#endif

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void ADC_init(const ADC_Config *config_ptr)
{
	/* insert the required voltage reference in the last tow bits (REFS1,REFS0)
	  of ADMUX Register */
	ADMUX = (ADMUX & 0x3F) | ((config_ptr->V_RF) << 6);

	/* insert the required Prescaler in the first three bits (ADPS0,ADPS1,ADPS2)
		   in ADCSRA Register */
		ADCSRA = (ADCSRA & 0xF8) | (config_ptr->prescaler);

	/* Enable ADC */
	ADCSRA |= (1<<ADEN);

#if(AUTO_TRIGGER_ENABLE == LOGIC_HIGH)
	/* Enable ADC Auto Trigger */
	ADCSRA |= (1<<ADATE);
	/* Select ADC Auto Trigger Source */
	SFIOR = (SFIOR & 0x1F) | ((config_ptr->trigger) << 5);
#endif

}

uint16 ADC_polling_readChannel(Channel_Selection channel)
{
	/* insert the required input channel in the first five bits (MUX0,MUX1,MUX2,MUX3,MUX4)
	   of ADMUX Register */
	ADMUX = (ADMUX & 0xE0) | (channel);

	/* ADC Start Conversion */
	SET_BIT(ADCSRA,ADSC);

	/* Wait till ADC finish Conversion and ADC Interrupt flag Set */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	/* Clear the ADC Interrupt flag */
	SET_BIT(ADCSRA,ADIF);

	return ADC;		/* return ADC value */
}

#if(INT_MODE == TRUE)
void ADC_INT_readChannel(Channel_Selection channel)
{
	/* Enable ADC Interrupt */
		ADCSRA |= (1<<ADIE);

	/* insert the required input channel in the first five bits (MUX0,MUX1,MUX2,MUX3,MUX4)
	   of ADMUX Register */
	ADMUX = (ADMUX & 0xE0) | (channel);

	/* ADC Start Conversion */
	ADCSRA |= (1<<ADSC);

}
#endif

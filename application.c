/*
 * application.c
 *
 *  Created on: ???/???/????
 *      Author: Omar
 */

#include "gpio.h"
#include "adc.h"
#include "lcd.h"
#include "dc_motor.h"
#include "lm35_tempsensor.h"
#include "pwm.h"
#include "bit_math.h"


int main(void)
{
	uint8 temp;

	ADC_Config adcConfig = {INTERNAL_VLOTAGE,ADC2,FACTOR_8};
	ADC_init(&adcConfig);

	LCD_init();
	dcMotor1_init();

	LCD_moveCursor(0,2);
	LCD_displayString("MOTOR IS OFF");

	temp = LM35_readTemperature(ADC2);

	LCD_moveCursor(1,2);
	LCD_displayString("Temp =    C");
	LCD_moveCursor(1,8);
	LCD_intgerToString(temp);


	while(1)
	{
		temp = LM35_readTemperature(ADC2);

		if(temp < 30){
			dcMotor1SetDirection(STOP,FAN_OFF);
			LCD_moveCursor(0,2);
			LCD_displayString("MOTOR IS OFF");
			LCD_moveCursor(1,8);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
			if(temp < 10){
				LCD_displayCharacter(' ');
			}

		}else if(temp >= 30 && temp < 60){
			dcMotor1SetDirection(CLOCK_WISE,SPEED25);
			LCD_moveCursor(0,2);
			LCD_displayString("MOTOR IS ON ");
			LCD_moveCursor(1,8);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');

		}else if(temp >= 60 && temp < 90){
			dcMotor1SetDirection(CLOCK_WISE,SPEED50);
			LCD_moveCursor(0,2);
			LCD_displayString("MOTOR IS ON ");
			LCD_moveCursor(1,8);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');

		}else if(temp >= 90 && temp < 120){
			dcMotor1SetDirection(CLOCK_WISE,SPEED75);
			LCD_moveCursor(0,2);
			LCD_displayString("MOTOR IS ON ");
			LCD_moveCursor(1,8);
			LCD_intgerToString(temp);
			if(temp < 100){
			LCD_displayCharacter(' ');
			}

		}else if(temp >= 120){
			dcMotor1SetDirection(CLOCK_WISE,SPEED_MAX);
			LCD_moveCursor(0,2);
			LCD_displayString("MOTOR IS ON ");
			LCD_moveCursor(1,8);
			LCD_intgerToString(temp);

		}else{
			/* do nothing */
		}

	}

	return 0;
}

/*
 * DutyCycle_Frequency_reader.c
 *
 * Created: 10/3/2023 7:59:35 PM
 *  Author: mahmo
 */ 


#include <avr/io.h>
#include "LCD.h"
#define F_CPU 8000000ul
#include <avr/delay.h>
#include "Timer.h"

int main(void)
{
	LCD_Init();
	unsigned short a,b,c,Ton;
	unsigned short period,duty_cycle,frequency;
	TCCR1A = 0;
	TIFR = (1<<ICF1);
	TCCR1B = 0xC1;
	while((TIFR&(1<<ICF1))==0);
	a = ICR1;
	TIFR = (1<<ICF1);
	
	TCCR1B = 0x81;
	while((TIFR&(1<<ICF1))==0);
	b = ICR1;
	TIFR = (1<<ICF1);
	
	TCCR1B = 0xC1;	
	while((TIFR&(1<<ICF1))==0);
	c = ICR1;
	TIFR = (1<<ICF1);
	
	TCCR1B = 0;
	

	
	if (a<b && b<c)
	{	
		Ton = b-a;
		period = c-a;//number of counts in 1 period
	
		duty_cycle = ((float)Ton/period)*100;
		frequency = F_CPU/period;//time period = period*(1/F_CPU)
		LCD_send_string("Duty Cycle:");
		LCD_sendChar((duty_cycle/10)+48);
		LCD_sendChar((duty_cycle%10)+48);
		LCD_sendChar("%");
		LCD_move_cursor(2,1);
		LCD_send_string("frequency:");
		LCD_sendChar((frequency/1000)+48);
		LCD_sendChar(((frequency/100)%10)+48);
		LCD_sendChar(((frequency/10)%10)+48);
		LCD_sendChar((frequency%10)+48);
		LCD_send_string("Hz");
	} 
	else
	{
		LCD_clear_screen();
		LCD_send_string("out of range");
	}
	while(1)
	{
		
	}
}
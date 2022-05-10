/*
 * Final_code_Member3.c
 *************************************************
 Author: Wickramasooriya H.P.E.
 First written: 11/15/2020
 Last updated: 05/04/2020

 MCU:Atmega32
 Crystal:16 MHz
 Platform:Atmel Studio 7

 PURPOSE:
 Tutorial Book Issuing System for Mr.Incognito
 ************************************************/

// 8 MHz crystal oscillator on my Development System.
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

//Include Files
#include "LED.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "DCMotor.h"

//Function prototype
/*void delay_ms();
void Green_LED();
void Red_LED();
void init_io();
void init_servo();
void SERVO_CLOCKWISE();
void SERVO_ANTI_CLOCKWISE();
void setup_wheel(void);
void wheel_Moving_front(void);
void move_round_front(void);
void move_angles_front(float angles);
void init_DC();
void DC_Rotate();
void DC_Stop();*/


//variables
int Teacher=0; //Check whether a teacher or not (If a teacher, Teacher=1)
int paid=1; //Check whether paid or not (If paid student, paid=1)
int num=1, No_of_execution=1;//# of execution of the entire code

int main(void)
{
	init_io();
	init_servo();
	setup_wheel();
	init_DC();
    while (1) 
    {
		if (Teacher==1)
		{
			//rest parts of the machine do not work
			//Door open
		}
		else
		{
	      if (paid==1)
	      {
			 Green_LED(); 
			 SERVO_CLOCKWISE();
			  wheel_Moving_front();
			 SERVO_ANTI_CLOCKWISE();
			 while(1)
			 {
				 DC_Rotate();
				 if(SENSE_IR_PORT & (1<<5))
				 {
					 DC_Stop();
					 break;
				 }
			 }
			
	      }
		  else
		  {
			  Red_LED();
		  }
		}
		//  num++;
    }
}

void Red_LED()
{
	//Code for blink Red LED
	LED_R_ON();
	_delay_ms(1000);
	LED_R_OFF();
	_delay_ms(1000);
}

void Green_LED()
{
	//Code for blink Red LED
	LED_G_ON();
	_delay_ms(1000);
	LED_G_OFF();
	_delay_ms(1000);
}


//function to get calculation according to our parameters of wheel, tutorial and step angle of stepper motor
void setup_wheel(void)
{
	DDRC = 0xFF;
	rounds_per_Round = 360/(angle*8); // to calculate no of rotations per round (1 because of 45 degrees step angle)
	round_length = (2*22/7*radius); // to calculate the length per rotation
	angle_length =round_length/360*angle; // to calculate the length per step angle
}

// function to move the conveyor(operate the stepper motor) as our requirement
void wheel_Moving_front(void)
{
	
	full_rounds = floor(move_length/round_length); // to calculate the number of rotations, motor should rotated
	balance_length = move_length - (full_rounds*round_length); // to calculate remaining length should completed by using step angles
	angle_needed = floor(balance_length/angle_length); // to calculate the remaining angles, motor should completed
	
	//this loop is executed until completing full rounds according to calculations
	for (int i=0; i<full_rounds; i++)
	{
		// this is executed until completing the no of rotations per round
		for (int j=0; j<rounds_per_Round; j++)
		{
			move_round_front();
		}
	}
	// to complete remaining angels
	move_angles_front(angle_needed);
}


//function to set a require pins as high or low
//according to the port energizing mechanism of a stepper motor
//Half step sequences (one-two phase excitation)
// function to complete a rotation
void move_round_front(void)
{
	PORTC = 0x01; // set a PC0 as high
	_delay_ms(period);
	PORTC = 0x05; // set both PC0 and PC2 as high
	_delay_ms(period);
	PORTC = 0x04; // set a PC2 as high
	_delay_ms(period);
	PORTC = 0x06; // set both PC1 and PC2 as high
	_delay_ms(period);
	PORTC = 0x02; // set a PC1 as high
	_delay_ms(period);
	PORTC = 0x0A; // set both PC1 and PC3 as high
	_delay_ms(period);
	PORTC = 0x08; // set a PC3 as high
	_delay_ms(period);
	PORTC = 0x09; // set both PC0 and PC3 as high
	_delay_ms(period);
	PORTC = 0x01; // set a PC0 as high
	_delay_ms(period);
}

// function to a complete relevant steps( remaining angles )
// angles = remaining angles to complete
void move_angles_front(float angles)
{
	int i=0;
	if (angles>0)
	{
		while (1)
		{
			PORTC = 0x01; // set a PC0 as high
			_delay_ms(period);
			PORTC = 0x05; // set both PC0 and PC2 as high
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x04; // set a PC2 as high
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x06; // set both PC1 and PC2 as high
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x02; // set a PC1 as high
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x0A; // set both PC1 and PC3 as high
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x08; // set a PC3 as high
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x09; // set both PC0 and PC3 as high
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x01; // set a PC0 as high
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
		}
	}
}
/*
 * ServoMotor.c
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

//Import the ServoMotor Header File
#include "ServoMotor.h"

//Function to initialize port settings
void init_servo()
{
	//Set Data Direction Register to output mode for
	// Servo Motor pin
	SERVO_DDR |= (1<<(SERVO_BIT));
}
// Function for Servo Motor Clockwise
void SERVO_CLOCKWISE()
{
	
	OUTPUT_SERVO_PORT |= 0x08; // set PB3 pin as high
	_delay_us(2000); // to get shaft position at +90 degrees of its rotation (2ms)
	OUTPUT_SERVO_PORT &= ~(0x08); // set PB3 pin as low
	_delay_ms(2000); 
	
	
}
// Function for Servo Motor Anti-Clockwise
void SERVO_ANTI_CLOCKWISE()
{
	_delay_ms(2000);
	OUTPUT_SERVO_PORT |= 0x08; // set PB3 pin as high
	_delay_us(1500); // to get shaft position at 0 degrees of its rotation (1.5ms)
	OUTPUT_SERVO_PORT &= ~(0x08); // set PB3 pin as low
	_delay_ms(2000);
}

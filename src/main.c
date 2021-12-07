/*
 * main.c
 *
 *  Created on: 30 nov. 2021
 *      Author: user
 */

#include "main.h"
#include "LPC8xx.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include "ctimer.h"
#include "swm.h"
#include "uart.h"
#include "chip_setup.h"
#include "utilities.h"
#include <string.h>
#include "GPIO_hexapode.h"
#include "UART_hexapode.h"
#include "CB_RX0.h"
#include "robotCommand.h"
#include "protocol.h"
#include "MRT_hexapode.h"

int main()
{
	init_peripherals();
	init_lcd();

	//Variables des boutons
	uint8_t currentBtn1State;
	uint8_t currentBtn2State;
	uint8_t prevBtn1State = BTN1;
	uint8_t prevBtn2State = BTN2;
	uint8_t rEdge1 = 0;
	uint8_t rEdge2 = 0;


	while(1)
	{
		//Lecture des front montants des boutons
		currentBtn1State = BTN1;
		currentBtn2State = BTN2;
		rEdge1 = telerupteur(BTN1_PIN, currentBtn1State, prevBtn1State);
		rEdge2 = telerupteur(BTN2_PIN, currentBtn2State, prevBtn2State);
		prevBtn1State = currentBtn1State;
		prevBtn2State = currentBtn2State;

		if (rEdge1 == 1)
		{
			LED1 = 1;
			while(!isAnswerReceived());
			setMotorPosition(3, (80));
			while(!isAnswerReceived());
			setMotorPosition(6, (80));
			while(!isAnswerReceived());
			setMotorPosition(9, (80));
		}
		else if (rEdge1 == 2)
		{
			LED1 = 0;
			while(!isAnswerReceived());
			setMotorPosition(3, (230));
			while(!isAnswerReceived());
			setMotorPosition(6, (230));
			while(!isAnswerReceived());
			setMotorPosition(9, (230));
		}
	}
}

void init_peripherals()
{
	//Overclock 15 MHz
	LPC_PWRD_API->set_fro_frequency(30000);

	// Activation du périphérique d'entrées/sorties TOR + timer + switch matrix
	LPC_SYSCON->SYSAHBCLKCTRL0 |= SWM;

	init_GPIO();
	init_UART0(115200);
	init_MRT0(1000);
}

uint8_t telerupteur(uint8_t btnPin, uint8_t currentBtnState, uint8_t prevBtnState)
{
	if (((prevBtnState) != currentBtnState) && currentBtnState == 0)
		return 1;
	else if (((prevBtnState) != currentBtnState) && currentBtnState == 1)
		return 2;
	else
		return 0;
}

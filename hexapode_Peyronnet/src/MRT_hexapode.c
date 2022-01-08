/*
 * MRT.c
 *
 *  Created on: 3 déc. 2021
 *      Author: Andre
 */

#include "MRT_hexapode.h"
#include <stdio.h>
#include "LPC8xx.h"
#include "syscon.h"
#include "mrt.h"
#include "toolbox.h"
#include "math.h"
#include "UART_hexapode.h"
#include "CB_TX0.h"
#include "robotCommand.h"

//Initialise le timer MRT
void init_MRT0(float frequency)
{
	LPC_SYSCON->SYSAHBCLKCTRL0 |= MRT;

	//Réglage MRT
	MRT0_setFrequency(frequency);
	LPC_MRT->Channel[0].CTRL = (1 << MRT_INTEN) | (0 << MRT_MODE);	//Interrupt Enable

	//Configuration des interruptions
	NVIC->ISER[0] |= (1 << (uint32_t)MRT_IRQn);	//Activation des interrupt MRT
	NVIC->IP[2] &= ~(0x00800000);						//Prio forte sur MRT
}

//Interruption
void MRT_IRQHandler()
{
	LPC_MRT->Channel[0].STAT |= (1 << MRT_INTFLAG);
	//Vérifier si on a des charactères à traiter (il n'y en a jamais puisque les moteurs n'envoient rien)
	if (CB_RX0_IsDataAvailable())
		decodeMessage(CB_RX0_Get());
	//Calcul de la nouvelle position des moteurs
	marche_sinus();

}

//Permet de changer la fréquence du timer
void MRT0_setFrequency(float frequency)
{
	LPC_MRT->Channel[0].INTVAL = (uint32_t)(FCLK / frequency); //Timer Period
}


/*
 * UART.c
 *
 *  Created on: 3 déc. 2021
 *      Author: Andre
 */

#include "UART_hexapode.h"
#include "syscon.h"
#include "LPC8xx.h"
#include "swm.h"
#include "chip_setup.h"
#include "uart.h"
#include "CB_RX0.h"
#include "CB_TX0.h"

void init_UART0(uint32_t baudrate)
{
	LPC_SYSCON->SYSAHBCLKCTRL0 |= UART0;
	LPC_SYSCON->UART0CLKSEL &= ~0b111; //UART Clk <- Free Run Oscillator

	LPC_USART0->CFG = 1 ;							//UART Enable, no parity, 1 stop bit, asynchronous, Normal mode,
	LPC_USART0->CFG |= (1 << 2);					//8 bits
	LPC_USART0->INTENSET |= RXRDY;					//Interruption sur reception d'un octet
	LPC_USART0->BRG = (uint32_t)BRGVAL(baudrate);	// baud

	NVIC->ISER[0] |= (1 << (uint32_t)UART0_IRQn);
	NVIC->IP[0] &= ~(0b11 << 30);

	ConfigSWM(U0_TXD, UART0_TX_PIN);		//TX -> Pin_TX
	ConfigSWM(U0_RXD, UART0_RX_PIN);		//RX -> Pin_RX
//	ConfigSWM(U0_TXD, DBGTXPIN);		//TX -> Pin_TX
//	ConfigSWM(U0_RXD, DBGRXPIN);		//RX -> Pin_RX
}

void UART0_IRQHandler()
{
	if (LPC_USART0->INTSTAT & RXRDY)
		CB_RX0_Add(LPC_USART0->RXDAT);
	else if (LPC_USART0->INTSTAT & TXIDLE)
		UART0_sendOne();
}

uint8_t UART0_checkCharacterReception(uint8_t *character)
{
	*character = 0;
	if (LPC_USART0->STAT & RXRDY)
	{
		*character = LPC_USART0->RXDAT;
		return 1;
	}
	else
		return 0;
}

void UART0_sendOne()
{
	//Fonction à n'appeler que lors de l'interruption TXIDLE
	if (CB_TX0_GetDataSize() > 0)
	{
		uint8_t value = CB_TX0_Get();
		LPC_USART0->TXDAT = value;
	}
	else
		UART0_endTransmission();
}

void UART0_beginTransmission()
{
	if (CB_TX0_GetDataSize() > 0)
		LPC_USART0->INTENSET |= TXIDLE;					//Interruption sur reception d'un octet
}

void UART0_endTransmission()
{
	LPC_USART0->INTENCLR |= TXIDLE;
	CB_TX0_endTransmission();
}

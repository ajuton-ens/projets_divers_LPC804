/*
 * CB_TX.c
 *
 *  Created on: 6 déc. 2021
 *      Author: Andre
 */

#include "CB_TX0.h"
#include "UART_hexapode.h"
#include "protocol.h"

#define CBTX0_BUFFER_SIZE 128

uint16_t cbTx0Head;
uint16_t cbTx0Tail;
uint8_t cbTx0Buffer[CBTX0_BUFFER_SIZE];
uint8_t isTransmitting = 0;

void SendMessage(uint8_t* message, uint16_t length)
{
	uint8_t i = 0;

    if (CB_TX0_RemainingSize() > length && isAnswerReceived())
    {
        //On peut écrire le message
        for (i = 0 ; i < length ; i++)
            CB_TX0_Add(message[i]);
        setAnswerWaiting();
        if (!isTransmitting)
        {
        	isTransmitting = 1;
        	UART0_beginTransmission();
        }
    }
}

void CB_TX0_Add(uint8_t value)
{
    cbTx0Buffer[cbTx0Head++] = value;
    if (cbTx0Head >= CBTX0_BUFFER_SIZE)
        cbTx0Head = 0;
}

uint8_t CB_TX0_Get()
{
	uint8_t temp = cbTx0Buffer[cbTx0Tail++];
    if (cbTx0Tail >= CBTX0_BUFFER_SIZE)
        cbTx0Tail = 0;
    return temp;
}

void CB_TX0_endTransmission()
{
	isTransmitting = 0;
}

uint16_t CB_TX0_RemainingSize()
{
	uint16_t rSize;

    if (cbTx0Head >= cbTx0Tail)
        rSize = CBTX0_BUFFER_SIZE - (cbTx0Head - cbTx0Tail);
    else
        rSize = CBTX0_BUFFER_SIZE - (CBTX0_BUFFER_SIZE - cbTx0Tail + cbTx0Head);
    return rSize;
}

uint16_t CB_TX0_GetDataSize()
{
	uint16_t dSizeTransmit;
    dSizeTransmit = CBTX0_BUFFER_SIZE - CB_TX0_RemainingSize();
    return dSizeTransmit;
}


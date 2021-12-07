/*
 * CB_RX.c
 *
 *  Created on: 6 déc. 2021
 *      Author: Andre
 */

#include "CB_RX0.h"

#define CBRX0_BUFFER_SIZE 128

uint16_t cbRx0Head, cbRx0Tail;
uint8_t cbRx0Buffer[CBRX0_BUFFER_SIZE];

void CB_RX0_Add(uint8_t value)
{
    if(CB_RX0_GetRemainingSize() > 0)
    {
        cbRx0Buffer[cbRx0Head++] = value;
        if(cbRx0Head >= CBRX0_BUFFER_SIZE)
            cbRx0Head = 0;
    }

}

uint8_t CB_RX0_Get()
{
	uint8_t value = cbRx0Buffer[cbRx0Tail++];
    if(cbRx0Tail >= CBRX0_BUFFER_SIZE)
        cbRx0Tail = 0;
    return value;
}

uint8_t CB_RX0_IsDataAvailable()
{
    if(cbRx0Head != cbRx0Tail)
        return 1;
    else
        return 0;
}

uint16_t CB_RX0_GetRemainingSize()
{
	uint16_t rSizeRecep;
    if (cbRx0Head >= cbRx0Tail)
        rSizeRecep = CBRX0_BUFFER_SIZE - (cbRx0Head - cbRx0Tail);
    else
        rSizeRecep = CBRX0_BUFFER_SIZE - (CBRX0_BUFFER_SIZE - cbRx0Tail + cbRx0Head);
    return rSizeRecep;
}
uint16_t CB_RX0_GetDataSize()
{
	uint16_t rSizeRecep;
    rSizeRecep = CBRX0_BUFFER_SIZE - CB_RX0_GetRemainingSize();
    return rSizeRecep;
}

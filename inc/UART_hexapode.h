/*
 * UART.h
 *
 *  Created on: 3 déc. 2021
 *      Author: Andre
 */

#ifndef INC_UART_HEXAPODE_
#define INC_UART_HEXAPODE_

#include "stdint.h"

//Define UART
#define FCLK 15000000.0
#define OSRVAL 0xF
#define BRGVAL(baudrate) (FCLK / (OSRVAL + 1) / baudrate - 0.5)

#define UART0_RX_PIN 11
#define UART0_TX_PIN 16

void init_UART0(uint32_t baudrate);
uint8_t UART0_checkCharacterReception(uint8_t *character);
void UART0_sendOne();
void UART0_beginTransmission();
void UART0_endTransmission();

#endif /* INC_UART_HEXAPODE_ */

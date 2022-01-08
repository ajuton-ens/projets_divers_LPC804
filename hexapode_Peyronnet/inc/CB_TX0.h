/*
 * CB_TX.h
 *
 *  Created on: 6 déc. 2021
 *      Author: Andre
 */

#ifndef INC_CB_TX_H_
#define INC_CB_TX_H_

#include <stdint.h>

void SendMessage(uint8_t*, uint16_t);
void CB_TX0_Add(unsigned char);
uint8_t CB_TX0_Get();
void CB_TX0_endTransmission();
uint16_t CB_TX0_RemainingSize();
uint16_t CB_TX0_GetDataSize();

#endif /* INC_CB_TX_H_ */

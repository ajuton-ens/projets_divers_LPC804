/*
 * CB_RX.h
 *
 *  Created on: 6 déc. 2021
 *      Author: Andre
 */

#ifndef INC_CB_RX_H_
#define INC_CB_RX_H_

#include <stdint.h>

void CB_RX0_Add(unsigned char);
uint8_t CB_RX0_Get();
uint8_t CB_RX0_IsDataAvailable();
uint16_t CB_RX0_GetRemainingSize();
uint16_t CB_RX0_GetDataSize();

#endif /* INC_CB_RX_H_ */

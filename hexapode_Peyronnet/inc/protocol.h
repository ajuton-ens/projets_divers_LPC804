/*
 * protocol.h
 *
 *  Created on: 30 nov. 2021
 *      Author: user
 */

#ifndef INC_PROTOCOL_H_
#define INC_PROTOCOL_H_

#include <stdint.h>

#define STATE_STARTBIT1 0
#define STATE_STARTBIT2 1
#define STATE_ID		2
#define STATE_LENGTH	3
#define STATE_ERROR		4
#define STATE_PAYLOAD	5
#define STATE_CHECKSUM	6

#define RECEIVED_BUFFER_SIZE 128

void encodeAndSendMessage(uint8_t nMotor, uint8_t length, uint8_t adress, uint8_t *payload);
void decodeMessage(uint8_t c);
void processDecodedMessage(uint8_t motorID, uint8_t length, uint8_t error, uint8_t *payload);
uint8_t calculateChecksum(uint8_t motorID, uint8_t length, uint8_t instruction, const uint8_t *payload);
uint8_t isAnswerReceived();
void setAnswerWaiting();
void setAnswerReceived();


#endif /* INC_PROTOCOL_H_ */

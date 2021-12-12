/*
 * protocol.c
 *
 *  Created on: 30 nov. 2021
 *      Author: user
 */

#include "protocol.h"
#include "CB_TX0.h"

uint8_t answerReceived = 1;

void encodeAndSendMessage(uint8_t motorID, uint8_t length, uint8_t instruction, uint8_t *payload)
{
	uint8_t message[length + 4];
	uint8_t i = 0, j;
	message[i++] = 0xff;															//Start bit 1
	message[i++] = 0xff;															//Start bit 2
	message[i++] = motorID;															//Motor ID
	message[i++] = length;															//Length (Instrution + Payload + Checksum)
	message[i++] = instruction;														//Instruction
	for (j = 0;j < length - 2; j++)
		message[i++] = payload[j];													//Payload
	message[i++] = calculateChecksum(motorID, length, instruction, payload);		//Checksum

	SendMessage(message, length + 4);
}

uint8_t receivedState = STATE_STARTBIT1;
uint8_t receivedID;
uint8_t receivedLength;
uint8_t receivedError;
uint8_t receivedPayload[RECEIVED_BUFFER_SIZE];
uint8_t receivedPayloadIndex = 0;
void decodeMessage(uint8_t c)
{
	switch(receivedState)
	{
		case STATE_STARTBIT1:
			setAnswerReceived();
			if (c == 0xff)
			{
				receivedState = STATE_STARTBIT2;
			}
			break;

		case STATE_STARTBIT2:
			receivedPayloadIndex = 0;
			if (c == 0xff)
				receivedState = STATE_ID;
			else
				receivedState = STATE_STARTBIT1;
			break;

		case STATE_ID:
			receivedID = c;
			receivedState = STATE_LENGTH;
			break;

		case STATE_LENGTH:
			receivedLength = c;
			receivedState = STATE_ERROR;
			break;

		case STATE_ERROR:
			receivedError = c;
			receivedState = STATE_PAYLOAD;
			break;

		case STATE_PAYLOAD:
			if (receivedLength - 2 > RECEIVED_BUFFER_SIZE)
				receivedState = STATE_STARTBIT1;
			else if (receivedPayloadIndex < receivedLength - 2)
				receivedPayload[receivedPayloadIndex++] = c;
			else
				receivedState = STATE_CHECKSUM;
			break;

		case STATE_CHECKSUM:
			if(c == calculateChecksum(receivedID, receivedLength, receivedError, receivedPayload))
				processDecodedMessage(receivedID, receivedLength, receivedError, receivedPayload);
			receivedState = STATE_STARTBIT1;
			break;
	}
}

void processDecodedMessage(uint8_t motorID, uint8_t length, uint8_t error, uint8_t *payload)
{
	//Fonction inutile pour l'instant, servira peut-être un jour...
	if (error == 0)
	{
		//pas d'erreur
	}
	else
	{
		//une erreur
	}
}

uint8_t calculateChecksum(uint8_t motorID, uint8_t length, uint8_t instruction, const uint8_t *payload)
{
	//La fonction marche aussi pour les trames recu, il faut remplacer instruction par error
	//checksum = ~(sum_i(message[i]))
	uint8_t checksum = motorID + length + instruction;
	uint8_t i = 0;
	for (i = 0; i < length - 2; i++)
		checksum += payload[i];
	checksum = ~checksum;
	return checksum;
}

uint8_t isAnswerReceived()
{
	return answerReceived;
}

void setAnswerWaiting()
{
	answerReceived = 0;
}

void setAnswerReceived()
{
	answerReceived = 1;
}

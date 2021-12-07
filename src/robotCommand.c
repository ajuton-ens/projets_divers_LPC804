/*
 * robotCommand.c
 *
 *  Created on: 6 déc. 2021
 *      Author: Andre
 */
#include "robotCommand.h"
#include "toolbox.h"
#include "protocol.h"

void setMotorPosition(uint8_t motorID, float position)
{
	uint16_t positionInt = (uint16_t)(position * 1023 /299.71);

	//Attention, lecture de la position dans le sens LSB -> MSB
	uint8_t i = 0;
	uint8_t payload[LENGTH_WRITE_GOAL_POSITION - 2];
	payload[i++] = ADDRESS_GOAL_POSITION;
	payload[i++] = positionInt & 0xff;
	payload[i++] = positionInt >> 8;
	encodeMessageAndSendMessage(motorID, LENGTH_WRITE_GOAL_POSITION, INSTRUCTION_WRITE, payload);
}

void initMotorLimits()
{

}

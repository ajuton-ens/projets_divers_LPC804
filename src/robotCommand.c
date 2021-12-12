/*
 * robotCommand.c
 *
 *  Created on: 6 déc. 2021
 *      Author: Andre
 */
#include "robotCommand.h"
#include "toolbox.h"
#include "protocol.h"

const uint16_t positionLowLimit[18] = {	 MOTOR1_LIMIT_L,
									   	 MOTOR2_LIMIT_L,
										 MOTOR3_LIMIT_L,
										 MOTOR4_LIMIT_L,
										 MOTOR5_LIMIT_L,
										 MOTOR6_LIMIT_L,
										 MOTOR7_LIMIT_L,
										 MOTOR8_LIMIT_L,
										 MOTOR9_LIMIT_L,
										 MOTOR10_LIMIT_L,
										 MOTOR11_LIMIT_L,
										 MOTOR12_LIMIT_L,
										 MOTOR13_LIMIT_L,
										 MOTOR14_LIMIT_L,
										 MOTOR15_LIMIT_L,
										 MOTOR16_LIMIT_L,
										 MOTOR17_LIMIT_L,
										 MOTOR18_LIMIT_L};

const uint16_t positionHighLimit[18] = {MOTOR1_LIMIT_H,
										MOTOR2_LIMIT_H,
										MOTOR3_LIMIT_H,
										MOTOR4_LIMIT_H,
										MOTOR5_LIMIT_H,
										MOTOR6_LIMIT_H,
										MOTOR7_LIMIT_H,
										MOTOR8_LIMIT_H,
										MOTOR9_LIMIT_H,
										MOTOR10_LIMIT_H,
										MOTOR11_LIMIT_H,
										MOTOR12_LIMIT_H,
										MOTOR13_LIMIT_H,
										MOTOR14_LIMIT_H,
										MOTOR15_LIMIT_H,
										MOTOR16_LIMIT_H,
										MOTOR17_LIMIT_H,
										MOTOR18_LIMIT_H};

void setMotorPosition(uint8_t motorID, float position)
{
	//Bornage de la position
	uint16_t positionInt = (uint16_t)(position * 1023 /299.71);
	positionInt = limitToInterval(positionInt, positionLowLimit[motorID - 1], positionHighLimit[motorID -1]);

	//Attention, lecture de la position dans le sens LSB -> MSB
	uint8_t i = 0;
	uint8_t payload[LENGTH_WRITE_GOAL_POSITION - 2];
	payload[i++] = ADDRESS_GOAL_POSITION;
	payload[i++] = positionInt & 0xff;
	payload[i++] = positionInt >> 8;
	encodeAndSendMessage(motorID, LENGTH_WRITE_GOAL_POSITION, INSTRUCTION_WRITE, payload);
}

void initMotorLimits()
{
	//TODO (or not todo...)
}



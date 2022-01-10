/*
 * robotCommand.h
 *
 *  Created on: 6 déc. 2021
 *      Author: Andre
 */

#ifndef INC_ROBOTCOMMAND_H_
#define INC_ROBOTCOMMAND_H_

#include <stdint.h>

//Instructions
#define INSTRUCTION_WRITE 0x03

//Length
#define LENGTH_WRITE_GOAL_POSITION 5

//Address
#define ADDRESS_GOAL_POSITION 30

//Angle limits
//M1: 	[124.22, 228.52]
//M2: 	[60.06, 220.90]
//M3: 	[73.24, 248.44]
//M4: 	[127.15, 170.21]
//M5: 	[60.06, 220.90]
//M6: 	[73.24, 248.44]
//M7: 	[88.48, 177.54]
//M8: 	[60.06, 220.90]
//M9: 	[73.24, 248.44]
//M10: 	[86.43, 171.39]
//M11: 	[60.06, 220.90]
//M12: 	[73.24, 248.44]
//M13: 	[127.15, 170.21]
//M14: 	[60.06, 220.90]
//M15: 	[73.24, 248.44]
//M16: 	[124.51, 210.35]
//M17: 	[60.06, 220.90]
//M18: 	[73.24, 248.44]
#define MOTOR1_LIMIT_L		424
#define MOTOR1_LIMIT_H		780
#define MOTOR2_LIMIT_L		205
#define MOTOR2_LIMIT_H		754
#define MOTOR3_LIMIT_L		250
#define MOTOR3_LIMIT_H		848
#define MOTOR4_LIMIT_L		434
#define MOTOR4_LIMIT_H		581
#define MOTOR5_LIMIT_L		205
#define MOTOR5_LIMIT_H		754
#define MOTOR6_LIMIT_L		250
#define MOTOR6_LIMIT_H		848
#define MOTOR7_LIMIT_L		302
#define MOTOR7_LIMIT_H		606
#define MOTOR8_LIMIT_L		205
#define MOTOR8_LIMIT_H		754
#define MOTOR9_LIMIT_L		250
#define MOTOR9_LIMIT_H		848
#define MOTOR10_LIMIT_L		295
#define MOTOR10_LIMIT_H		585
#define MOTOR11_LIMIT_L		205
#define MOTOR11_LIMIT_H		754
#define MOTOR12_LIMIT_L		250
#define MOTOR12_LIMIT_H		848
#define MOTOR13_LIMIT_L		434
#define MOTOR13_LIMIT_H		581
#define MOTOR14_LIMIT_L		205
#define MOTOR14_LIMIT_H		754
#define MOTOR15_LIMIT_L		250
#define MOTOR15_LIMIT_H		848
#define MOTOR16_LIMIT_L		425
#define MOTOR16_LIMIT_H		718
#define MOTOR17_LIMIT_L		205
#define MOTOR17_LIMIT_H		754
#define MOTOR18_LIMIT_L		250
#define MOTOR18_LIMIT_H		848

//geometrie de l'hexapode
#define XDD0 141.42
#define YDD0 141.42
#define XDD1 200.0
#define YDD1 0.0
#define XDD2 141.42
#define YDD2 -141.42
#define XDD3 -141.42
#define YDD3 141.42
#define XDD4 -200.0
#define YDD4 0.0
#define XDD5 -141.42
#define YDD5 -141.42
#define ZDD -50.0

#define L1 100.0
#define l1 55.0
#define l2 65.0
#define l3 70.0

#define T_ECH_MARCHE_ROBOT 0.1

void setMotorPosition(uint8_t motorID, float position);
void initMotorLimits();
void marche_sinus();
void robotSetVitesse(float value);
void robotSetAmplitude(float value);
void robotSetDirection(short value);


#endif /* INC_ROBOTCOMMAND_H_ */

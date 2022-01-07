/*
 * robotCommand.c
 *
 *  Created on: 6 déc. 2021
 *      Author: Andre
 */
#include "robotCommand.h"
#include "toolbox.h"
#include "protocol.h"
#include <math.h>

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

float vitesse = 0;
float amplitude = 0;
short direction = 0;
short rotation = 0;


void robotSetVitesse(float value)
{
	vitesse = value;
}

void robotSetAmplitude(float value)
{
	amplitude = value;
}

void robotSetDirection(short value)
{
	direction = value;
}

void marche_sinus()
{
	unsigned char n_patte;
	float servo[6][3];
	float xdd[6],ydd[6],zdd[6];
	const float xddinit[6]={XDD0,XDD1,XDD2,XDD3,XDD4,XDD5};
	const float yddinit[6]={YDD0,YDD1,YDD2,YDD3,YDD4,YDD5};
	const float zddinit[6]={ZDD,ZDD,ZDD,ZDD,ZDD,ZDD};
	float cosp,cosi,sinp,sini,xd,yd,teta1,teta2,teta3,alpha;
	static float omega, t=0, Ampp=0,Ampi=0,dir,dirp,diri,Ampiz,Amppz;
	const float gamma[6]={PI/4,0,-PI/4,3.0*PI/4,-PI,-3.0*PI/4};
	static char drapeaup=0, drapeaui=0,sens_rot=0, sens_rotp=0, sens_roti=0, avance;

	if (amplitude < 0)
		amplitude = - amplitude;
	if (amplitude > 30.0)
		amplitude = 30.0;

	if(rotation == 'h')
		sens_rot = -1;
	else if (rotation == 't')
		sens_rot = +1;
	else sens_rot = 0;

	if (vitesse < 0)
		vitesse = 0;

	if (vitesse > 10)
		vitesse = 10;

	direction += 180; 						//Correction débile pour que le robot avance tout droit à 0°
	dir = (float)direction*PI/180.0; 	//passage en radian de la direction
	if (dir < 0)
		avance = 0;
	else avance = 1;

	if (t==0)
	{
		Ampiz = amplitude;
		Amppz = amplitude;
	}

	if(vitesse == 0.0)  amplitude = 0;

	//modif de la valeur de omega que lorsque les pattes sont en haut
	if((omega != vitesse) && (vitesse != 0.0))
	{
		//t = omega*t/vitesse;
		omega = vitesse;
	}

	//modif de Ampp ou dirp quand les pattes paires sont en haut
	if ((Ampp != amplitude) || (dirp != dir) || (sens_rotp != sens_rot))
	{
		alpha = (-omega*t+PI)-2*PI*floorf((-omega*t+PI)/(2*PI));
		if ( (alpha < PI) && (alpha > (PI/2)))
			drapeaup=1;
		if ( (alpha < (PI/2)) && (drapeaup == 1))
		{
			Ampp = amplitude;
			Amppz= amplitude;
			dirp = dir;
			sens_rotp=sens_rot;
		}
	}

	//modif de Ampi quand les pattes impaires sont en haut
	if ((Ampi != amplitude)	|| (diri != dir) || (sens_roti != sens_rot))
	{
		alpha = (-omega*t)-2*PI*floorf((-omega*t)/(2*PI));
		if ((alpha < PI) && (alpha > (PI/2)))
			drapeaui=1;
		if ((alpha < (PI/2))&&(drapeaui == 1))
		{
			Ampi = amplitude;
			Ampiz= amplitude;
			diri = dir;
			sens_roti = sens_rot;
		}
	}

	if ((Ampp==amplitude) && (dirp==dir) && (sens_rotp==sens_rot))
			drapeaup = 0;

	if ((Ampi==amplitude) && (diri==dir) && (sens_roti==sens_rot))
			drapeaui = 0;


	t=t+T_ECH_MARCHE_ROBOT;
	cosp = cos(-omega*t+PI); //pour les pattes paires
	sinp = sin(-omega*t+PI);
	cosi = cos(-omega*t);  	//pour les pattes impaires
	sini = sin(-omega*t);

	//calcul des positions cartésiennes des pattes paires
	for(n_patte=0;n_patte<6;n_patte=n_patte+2)
	{
		zdd[n_patte]=zddinit[n_patte]+Amppz*sinp;
	}
		xdd[0]=xddinit[0]-Ampp*cosp*(sens_rotp*sin(PIsur4)+avance*sin(dirp));
		ydd[0]=yddinit[0]+Ampp*cosp*(sens_rotp*cos(PIsur4)+avance*cos(dirp));
		xdd[2]=xddinit[2]-Ampp*cosp*(sens_rotp*sin(-PIsur4)+avance*sin(dirp));
		ydd[2]=yddinit[2]+Ampp*cosp*(sens_rotp*cos(-PIsur4)+avance*cos(dirp));
		xdd[4]=xddinit[4]-Ampp*cosp*(sens_rotp*sin(PI)+avance*sin(dirp));
		ydd[4]=yddinit[4]+Ampp*cosp*(sens_rotp*cos(PI)+avance*cos(dirp));


	for(n_patte=1;n_patte<6;n_patte=n_patte+2)
	{
		zdd[n_patte]=zddinit[n_patte]+Ampiz*sini;
	}
		xdd[1]=xddinit[1]-Ampi*cosi*(sens_roti*sin(0)+avance*sin(diri));
		ydd[1]=yddinit[1]+Ampi*cosi*(sens_roti*cos(0)+avance*cos(diri));
		xdd[3]=xddinit[3]-Ampi*cosi*(sens_roti*sin(3*PIsur4)+avance*sin(diri));
		ydd[3]=yddinit[3]+Ampi*cosi*(sens_roti*cos(3*PIsur4)+avance*cos(diri));
		xdd[5]=xddinit[5]-Ampi*cosi*(sens_roti*sin(-3*PIsur4)+avance*sin(diri));
		ydd[5]=yddinit[5]+Ampi*cosi*(sens_roti*cos(-3*PIsur4)+avance*cos(diri));



	/*********************************************************
	// CALCUL DES ANGLES DES SERVOS-MOTEURS DE CHAQUE PATTE //
	// utilisation du modèle inverse de Jerome Chemouny     //
	*********************************************************/

	for(n_patte=0;n_patte<6;n_patte++)
	{
		//teta1
		teta1=180.0/PI*(atan2((ydd[n_patte]-L1*sin(gamma[n_patte])),(xdd[n_patte]-L1*cos(gamma[n_patte])))-gamma[n_patte]);
		if(teta1>180.0)
			teta1=teta1-360.0;
		servo[n_patte][0]=150.0+teta1;

		//teta2
		xd=sqrt(pow((ydd[n_patte]-L1*sin(gamma[n_patte])),2)+pow((xdd[n_patte]-L1*cos(gamma[n_patte])),2))-l1;
		yd=zdd[n_patte];
		teta2=180.0/PI*(-atan2(-yd,xd)+acos(((l3*l3)-(xd*xd)-(yd*yd)-(l2*l2))/(-2*l2*sqrt((xd*xd)+(yd*yd)))));
		servo[n_patte][1]=(150.0+teta2);

		//teta3
		teta3=180.0/PI*(PI/2-acos((-(l3*l3)+(xd*xd)+(yd*yd)-(l2*l2))/(-2*l2*l3)));
		servo[n_patte][2]=(teta3+150.0);
	}

	//envoi des ordres aux pattes
	for(n_patte=0;n_patte<6;n_patte++)
		for (int nMoteur = 0; nMoteur < 3; nMoteur++)
			setMotorPosition(n_patte*3 + nMoteur + 1, servo[n_patte][nMoteur]);
}

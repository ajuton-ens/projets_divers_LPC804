/*
 * GPIO.c
 *
 *  Created on: 3 déc. 2021
 *      Author: Andre
 */

#include <GPIO_hexapode.h>
#include "LPC8xx.h"
#include "syscon.h"


void init_GPIO()
{
	LPC_SYSCON->SYSAHBCLKCTRL0 |= GPIO;

	LPC_GPIO_PORT->DIR0 |= (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN);
}


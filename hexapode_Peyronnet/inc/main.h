#ifndef INC_MAIN_H
#define INC_MAIN_H

#include <stdint.h>

void init_peripherals();
uint8_t telerupteur(uint8_t btnPin, uint8_t currentBtnState, uint8_t prevBtnState);


#endif

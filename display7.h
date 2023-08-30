#ifndef __DISPLAY7_H__
#define __DISPLAY7_H__

#include <Arduino.h>
extern uint8_t pinA, pinB, pinC, pinD, pinE, pinnF, pinG, pindP;

//Función para conf. display de 7 seg
void configurarDisplay7(uint8_t pA, uint8_t pB, uint8_t pC, uint8_t pD, uint8_t pE, uint8_t pinF, uint8_t pG, uint8_t pdP);

//Función para desplegar valor al 7 seg
void desplegarValor(uint8_t valor);

//Función para desplegar dp en el 7 seg
void desplegarPunto(boolean punto);

#endif // __DISPLAY7_H__

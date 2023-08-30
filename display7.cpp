#include "display7.h"

uint8_t pinA, pinB, pinC, pinD, pinE, pinnF, pinG, pindP;

//Función para conf. display de 7 seg
void configurarDisplay7(uint8_t pA, uint8_t pB, uint8_t pC, uint8_t pD, uint8_t pE, uint8_t pinF, uint8_t pG, uint8_t pdP){
    pinA = pA;
    pinB = pB;
    pinC = pC;
    pinD = pD;
    pinE = pE;
    pinnF = pinF;
    pinG = pG;
    pindP = pdP;

    //Conf de todos los pines como salidas
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);
    pinMode(pinE, OUTPUT);
    pinMode(pinnF, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pindP, OUTPUT);

    //Conf de todos los pines para apagarlos
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinnF, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pindP, LOW);
}

//Función para desplegar valor al 7 seg
void desplegarValor(uint8_t valor){
    switch(valor){
    case 0: //config para número 0
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinnF, HIGH);
      digitalWrite(pinG, LOW);
      digitalWrite(pindP, LOW);
      break;
          
    case 1: //config para número 1
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinnF, LOW);
      digitalWrite(pinG, LOW);
      digitalWrite(pindP, LOW);
      break;

    case 2: //config para número 2
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinnF, LOW);
      digitalWrite(pinG, HIGH);
      digitalWrite(pindP, LOW);
      break;

    case 3: //config para número 3
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinnF, LOW);
      digitalWrite(pinG, HIGH);
      digitalWrite(pindP, LOW);
      break;

    case 4: //config para número 4
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinnF, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pindP, LOW);
      break;

    case 5: //config para número 5
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinnF, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pindP, LOW);
      break;

    case 6: //config para número 6
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinnF, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pindP, LOW);
      break;

    case 7: //config para número 7
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinnF, LOW);
      digitalWrite(pinG, LOW);
      digitalWrite(pindP, LOW);
      break;

    case 8: //config para número 8
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinnF, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pindP, LOW);
      break;

    case 9: //config para número 9
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinnF, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pindP, LOW);
      break;

    default:
      break;
    }
}

//Función para desplegar dp en el 7 seg
void desplegarPunto(boolean punto) {
    if (punto) {
        digitalWrite(pindP, HIGH);
    } else {
        digitalWrite(pindP, LOW);
    }
}

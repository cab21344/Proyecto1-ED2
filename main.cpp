// Electrónica Digital 2 - Proyecto 1
// María Daniela Cabrera Porras, 21344

// Librerías ************************************************************************************************
#include <Arduino.h>
#include "config.h"
#include "display7.h"
#include "driver/ledc.h"
#include "esp_adc_cal.h" //mejor lectura del ADC
//**********************************************************************************************************

// Canales **************************************************************************************************
#define pwmChannel 0      // canal servo
#define verdeChannel 1    // canal led verde
#define amarilloChannel 2 // canal led amarilla
#define rojoChannel 3     // canal led roja
#define freqLeds 500      // freq en Hz leds
//**********************************************************************************************************

// Pines display ********************************************************************************************
#define pA 21
#define pB 19
#define pC 18
#define pD 5
#define pE 17
#define pinF 16
#define pG 4
#define pdP 2

#define display1 27
#define display2 12
#define display3 13
//**********************************************************************************************************

// Pines leds, boton y sensor *******************************************************************************
const int servoPin = 15;
const int botonPin = 26;
const int amarilloPin = 33;
const int verdePin = 25;
const int rojoPin = 32;
const int lm35Pin = 36;
//**********************************************************************************************************

// Variables ************************************************************************************************
const int pwmMin = 77;
const int pwmMax = 255;

bool medirTemp = false;
float temp = 0.0;
//**********************************************************************************************************

// leer temp en adafruit ************************************************************************************
float temperatura = 0.0;
// set up the 'Canal temperatura' feed
AdafruitIO_Feed *tempCanal = io.feed("temperatura");
//********************************************************************************************************

void setup()
{
  // start the serial connection
  Serial.begin(115200);
  // wait for serial monitor to open
  while (!Serial);
  Serial.print("Connecting to Adafruit IO");

  // Connect to io.adafruit.com ****************************************************************************
  io.connect();
  // wait for a connection
  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  //********************************************************************************************************

  // Configurar boton y sensor como inputs ******************************************************************
  pinMode(lm35Pin, INPUT);
  pinMode(botonPin, INPUT_PULLUP);
  //********************************************************************************************************

  // Configurar como salida leds ****************************************************************************
  pinMode(verdePin, OUTPUT);
  pinMode(amarilloPin, OUTPUT);
  pinMode(rojoPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  //********************************************************************************************************

  // Configuración canales y pined de leds y servo ***********************************************************
  ledcSetup(rojoChannel, freqLeds, 8);
  ledcAttachPin(rojoPin, rojoChannel); // se asocia pin rojo con canal rojo
  ledcSetup(verdeChannel, freqLeds, 8);
  ledcAttachPin(verdePin, verdeChannel); // se asocia pin verde con canal verde
  ledcSetup(amarilloChannel, freqLeds, 8);
  ledcAttachPin(amarilloPin, amarilloChannel); // se asocia pin amarillo con canal amarillo

  ledcSetup(pwmChannel, 50, 10);
  ledcAttachPin(servoPin, pwmChannel);
  //********************************************************************************************************

  // Configurar display de 7 seg
  configurarDisplay7(pA, pB, pC, pD, pE, pinF, pG, pdP);

  pinMode(display1, OUTPUT);
  pinMode(display2, OUTPUT);
  pinMode(display3, OUTPUT);
  //********************************************************************************************************
}

void loop()
{
  // Parte 1, 2 y 3 ******************************************************************************************
  int estadoBoton = digitalRead(botonPin); //verifica si se precionó el botón 

  if (estadoBoton == LOW)
  {
    medirTemp = true; //si se presiona el botón hace que se empieze a medir la temp
  }

  if (medirTemp)
  {
    float valorTemp = analogRead(lm35Pin); //obtiene el valor del sensor
    Serial.print("ADC: ");
    Serial.println(valorTemp); //envía el valor obtenido del sensor

    temperatura = (valorTemp * 3300.0) / (4095.0 * 10.0); //Convierte de ADC a ºC
    temperatura = temperatura + 10;
    Serial.print("Temperatura: ");
    Serial.println(temperatura); //envía el valor convertido a ºC

    medirTemp = false; //cambia valor a false para que ya no mida temp

    // envia valor de temp a Adafruit ***********************************************************************
    io.run();                    // para que esté conectado al servidor de Adafruit
    Serial.print("sending -> "); // muestr en el serial monitor que valores manda
    Serial.println(temperatura);
    tempCanal->save(temperatura);
    //********************************************************************************************************

  }

  if (temperatura < 37.0) //si la temp es menor a 37º
  {
    ledcWrite(rojoChannel, 0);
    ledcWrite(verdeChannel, 255); // enciende led verde
    ledcWrite(amarilloChannel, 0);

    int dutyCycle = map(180, 0, 180, 26, 123); // mueve el servo a 180º
    ledcWrite(pwmChannel, dutyCycle);
    delay(5); // debounce
  }
  else if (temperatura >= 37.0 && temperatura < 37.5) //si la temp está entre 37º y 37.5º
  {
    ledcWrite(rojoChannel, 0);
    ledcWrite(verdeChannel, 0);
    ledcWrite(amarilloChannel, 255); // enciende led amarilla

    int dutyCycle = map(90, 0, 180, 26, 123); // mueve el servo a 90º
    ledcWrite(pwmChannel, dutyCycle);
    delay(5); // debounce
  }
  else //si la temp es mayor a 37º
  {
    ledcWrite(rojoChannel, 255); // enciende led amarilla
    ledcWrite(verdeChannel, 0);
    ledcWrite(amarilloChannel, 0);

    int dutyCycle = map(0, 0, 180, 26, 123); // mueve el servo a 0º
    ledcWrite(pwmChannel, dutyCycle);
    delay(5); // debounce
  }

  medirTemp = false; // que no siga obteniendo el valor de temp hasta volver a presionar el botón
  delay(5);          // debounce
  //********************************************************************************************************

  // Display de 7 seg ****************************************************************************************
  temp = temperatura * 10;
  int decena = temp / 100; //operación para mostrar el valor de la decena
  temp = temp - (decena * 100);
  int unidad = temp / 10; //operación para mostrar el valor de la unidad
  temp = temp - (unidad * 10);
  int decimal = temp; //operación para mostrar el valor de la decimal

  desplegarValor(decena); //despliega el valor de decena
  digitalWrite(display1, HIGH); //se muestra el valor de decena en el display1
  digitalWrite(display2, LOW);
  digitalWrite(display3, LOW);
  delay(5);

  desplegarValor(unidad); //despliega el valor de unidad
  digitalWrite(display1, LOW);
  digitalWrite(display2, HIGH); //se muestra el valor de unidad en el display2
  digitalWrite(display3, LOW);
  desplegarPunto(HIGH);
  delay(5);

  desplegarValor(decimal); //despliega el valor de decimal
  digitalWrite(display1, LOW);
  digitalWrite(display2, LOW);
  digitalWrite(display3, HIGH); //se muestra el valor de decimal en el display3
  delay(5);
}

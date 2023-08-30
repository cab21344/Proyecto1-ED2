/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME  "danicab3"
#define IO_KEY       "aio_KeLA40yVXm6qCjb4ZdAB7nNren3a"

/******************************* WIFI **************************************/
#define WIFI_SSID "iPhone de Dani"
#define WIFI_PASS "123456789"

#include "AdafruitIO_WiFi.h"


AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

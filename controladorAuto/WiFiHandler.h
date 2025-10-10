#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <Arduino.h>

// Definimos los dos posibles modos de operación para que el código sea más legible
enum ModosOperacion {
  MODE_AP,      // Access Point: El Wemos crea la red
  MODE_CLIENT   // Client/Station: El Wemos se conecta a una red existente
};

// Revisa el MODE_PIN e inicializa el WiFi en el modo correspondiente.
// Devuelve el modo que fue seleccionado.
ModosOperacion wifi_init();

// Obtiene un comando. La forma de obtenerlo depende del modo de operación.
String wifi_get_command();

#endif // WIFI_HANDLER_H
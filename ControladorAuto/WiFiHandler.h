#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <Arduino.h>

// Inicializa el WiFi en modo Access Point y levanta el servidor web.
void wifi_init();

// Escucha peticiones de clientes y devuelve el comando recibido.
String wifi_get_command();

#endif // WIFI_HANDLER_H
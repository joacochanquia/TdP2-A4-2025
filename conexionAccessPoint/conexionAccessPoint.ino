#include "WiFiHandler.h"

/************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando Servidor de Control en ESP32...");

  // Inicializa el WiFi, el servidor y las rutas
  server_init();

  Serial.println("Servidor HTTP iniciado. Esperando clientes...");
}

/************************************************************/
void loop() {
  // Deja que el manejador del servidor atienda las peticiones
  server_handle_client();
}
/************************************************************/
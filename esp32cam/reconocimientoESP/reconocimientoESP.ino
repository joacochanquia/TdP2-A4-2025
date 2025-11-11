#include "WiFiHandler.h"
#include "CameraHandler.h"

/************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando Servidor de Control en ESP32...");

  // Inicializa el WiFi, el servidor y las rutas
  server_init();

  // 2. Inicializa la cámara Y el servidor de streaming (puerto 82)
  setup_camera_handler();

  Serial.println("Servidor HTTP iniciado. Esperando clientes...");
}

/************************************************************/
void loop() {
  server_handle_client();
}
/************************************************************/
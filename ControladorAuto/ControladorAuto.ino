#include "config.h"
#include "MotorControl.h"
#include "WiFiHandler.h"

/************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando controlador del auto...");

  // Inicializa los motores
  auto_init();
  
  // Inicializa el WiFi
  wifi_init();

  Serial.println("Sistema listo.");
}

/************************************************************/
void loop() {
  
  // Obtiene el siguiente comando desde el servidor web
  String command = wifi_get_command();

  // Si se recibió un comando, procesarlo
  if (command.length() > 0) {
    Serial.print("Comando recibido: ");
    Serial.println(command);

    if (command == CMD_AVANZAR) {
      auto_avanzar();
    } else if (command == CMD_REVERSA) {
      auto_reversa();
    } else if (command == CMD_GIRO_DERECHA) {
      auto_giro_horario();
    } else if (command == CMD_GIRO_IZQUIERDA) {
      auto_giro_antihorario();
    } else if (command == CMD_DETENER) {
      auto_detener();
    }
  }
}
/************************************************************/
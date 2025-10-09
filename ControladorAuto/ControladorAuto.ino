#include "config.h"
#include "MotorControl.h"
#include "WiFiHandler.h"

// Variable global para almacenar el modo de operación actual
ModosOperacion modoActual;

/************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando controlador del auto...");

  auto_init();
  
  // Inicializa el WiFi y detecta el modo de operación
  modoActual = wifi_init();

  Serial.println("Sistema listo.");
}

/************************************************************/
void loop() {
  
  // Obtiene el siguiente comando. La función se encarga de la lógica
  // de si debe escuchar como servidor o preguntar como cliente.
  String command = wifi_get_command();

  // Si se recibió un comando, procesarlo
  if (command.length() > 0) {
    Serial.print("Comando recibido: ");
    Serial.println(command);

    // El procesamiento de comandos es idéntico para ambos modos
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
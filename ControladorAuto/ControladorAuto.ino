#include "config.h"
#include "MotorControl.h"
#include "WiFiHandler.h"

// Variable global para almacenar el modo de operación actual
OperatingMode currentMode;

/************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando controlador del auto...");

  motors_init();
  
  // Inicializa el WiFi y detecta el modo de operación
  currentMode = wifi_init();

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
    if (command == CMD_ADVANCE) {
      car_advance();
    } else if (command == CMD_REVERSE) {
      car_reverse();
    } else if (command == CMD_TURN_CLOCKWISE) {
      car_turn_clockwise();
    } else if (command == CMD_TURN_COUNTER_CW) {
      car_turn_counter_clockwise();
    } else if (command == CMD_STOP) {
      car_stop();
    }
  }

  
}
/************************************************************/
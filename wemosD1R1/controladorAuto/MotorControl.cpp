#include <Servo.h>
#include "config.h"
#include "MotorControl.h"

// Crear objetos Servo para cada motor
Servo servoLeft;
Servo servoRight;

void auto_init() {
  // Conectar los servos
  servoLeft.attach(SERVO_LEFT_PIN);
  servoRight.attach(SERVO_RIGHT_PIN);

  // Asegurarse de que los motores estén detenidos al iniciar
  auto_detener();
}

void auto_detener() {
  servoLeft.write(90);
  servoRight.write(90);
}

void auto_avanzar() {
  // Para avanzar, ambos servos giran en direcciones opuestas
  servoLeft.write(180);
  servoRight.write(0);
}

void auto_reversa() {
  // Para ir en reversa, se invierte la dirección de avance
  servoLeft.write(0);
  servoRight.write(180);
}

void auto_giro_horario() {
  // Para girar en sentido horario, ambos motores giran al mismo lado
  servoLeft.write(180);
  servoRight.write(180);
}

void auto_giro_antihorario() {
  // Para girar en sentido antihorario, se invierte la dirección del giro
  servoLeft.write(0);
  servoRight.write(0);
}
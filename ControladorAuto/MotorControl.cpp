#include <Servo.h>
#include "config.h"
#include "MotorControl.h"

// Crear objetos Servo para cada motor
Servo servoLeft;
Servo servoRight;

void motors_init() {
  // Conectar los servos a los pines definidos en config.h
  servoLeft.attach(SERVO_LEFT_PIN);
  servoRight.attach(SERVO_RIGHT_PIN);

  // Asegurarse de que los motores estén detenidos al iniciar
  car_stop();
}

void car_stop() {
  // Un valor de 90 microsegundos generalmente detiene un servo 360
  servoLeft.write(90);
  servoRight.write(90);
}

void car_advance() {
  // Para avanzar, ambos servos giran en direcciones opuestas
  // Nota: Puede que necesites invertir 0 y 180 dependiendo de cómo montaste los servos
  servoLeft.write(0);
  servoRight.write(180);
}

void car_reverse() {
  // Para ir en reversa, se invierte la dirección de avance
  servoLeft.write(180);
  servoRight.write(0);
}

void car_turn_clockwise() {
  // Para girar en sentido horario, ambos motores giran "hacia adelante"
  servoLeft.write(0);
  servoRight.write(0);
}

void car_turn_counter_clockwise() {
  // Para girar en sentido antihorario, ambos motores giran "hacia atrás"
  servoLeft.write(180);
  servoRight.write(180);
}
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

// Inicializa los pines y los objetos Servo
void motors_init();

// Funciones para controlar las acciones del auto
void car_advance();
void car_stop();
void car_reverse();
void car_turn_clockwise();
void car_turn_counter_clockwise();

#endif // MOTOR_CONTROL_H
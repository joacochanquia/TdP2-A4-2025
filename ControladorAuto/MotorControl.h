#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

// Inicializa los pines y los objetos Servo
void auto_init();

// Funciones para controlar las acciones del auto
void auto_avanzar();
void auto_detener();
void auto_reversa();
void auto_giro_horario();
void auto_giro_antihorario();

#endif // MOTOR_CONTROL_H
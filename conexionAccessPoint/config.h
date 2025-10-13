#ifndef CONFIG_H
#define CONFIG_H

#include <WiFi.h>

// =================================================================
// ==           CONFIGURACIÓN DEL ACCESS POINT (AP)               ==
// =================================================================
#define AP_WIFI_SSID "ESP_AccessPoint"      // Nombre de la red que creará el ESP32
#define AP_WIFI_PASSWORD "12345678"     // Contraseña de la red
#define AP_SERVER_IP   192,168,4,1


// =================================================================
// ==               DEFINICIÓN DE COMANDOS                        ==
// =================================================================
#define CMD_AVANZAR         "AVANZAR"
#define CMD_DETENER         "DETENER"
#define CMD_REVERSA         "REVERSA"
#define CMD_GIRO_DERECHA    "GIRO_DERECHA"
#define CMD_GIRO_IZQUIERDA  "GIRO_IZQUIERDA"

#endif // CONFIG_H
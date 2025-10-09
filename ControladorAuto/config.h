#ifndef CONFIG_H
#define CONFIG_H

// =================================================================
// ==                  CONFIGURACIÓN DE PINES                     ==
// =================================================================
#define SERVO_LEFT_PIN D7   // Pin para el servo izquierdo
#define SERVO_RIGHT_PIN D6  // Pin para el servo derecho


// =================================================================
// ==           CONFIGURACIÓN MODO ACCESS POINT (AP)              ==
// =================================================================
#define AP_WIFI_SSID "AutoESP8266"      // Nombre de la red WiFi que creará el Wemos
#define AP_WIFI_PASSWORD "12345678"     // Contraseña de la red
#define AP_SERVER_IP   10,10,10,10      // IP estática del servidor web


// =================================================================
// ==               DEFINICIÓN DE COMANDOS HTTP                   ==
// =================================================================
#define CMD_AVANZAR         "AVANZAR"
#define CMD_DETENER         "DETENER"
#define CMD_REVERSA        "REVERSA"
#define CMD_GIRO_DERECHA   "GIRO_DERECHA"
#define CMD_GIRO_IZQUIERDA "GIRO_IZQUIERDA"

#endif // CONFIG_H
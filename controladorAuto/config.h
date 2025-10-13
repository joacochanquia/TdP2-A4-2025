#ifndef CONFIG_H
#define CONFIG_H

// =================================================================
// ==                  CONFIGURACIÓN DE PINES                     ==
// =================================================================
#define SERVO_LEFT_PIN D7   // Pin para el servo izquierdo
#define SERVO_RIGHT_PIN D6  // Pin para el servo derecho

#define MODE_PIN D5         // Pin para seleccionar el modo.
#define CLIENT_MODE_VALUE LOW         // Valor para seleccionar el modo cliente.


// =================================================================
// ==           CONFIGURACIÓN MODO ACCESS POINT (AP)              ==
// =================================================================
#define AP_WIFI_SSID "AutoESP8266"      // Nombre de la red WiFi que creará el Wemos
#define AP_WIFI_PASSWORD "12345678"     // Contraseña de la red
#define AP_SERVER_IP   192,168,4,1      // IP estática del servidor web


// =================================================================
// ==               CONFIGURACIÓN MODO CLIENTE (STA)              ==
// =================================================================
#define CLIENT_WIFI_SSID "ESP_AccessPoint"  // El nombre de la red a la que te conectarás
#define CLIENT_WIFI_PASSWORD "12345678"  // La contraseña de esa red

// Dirección del servidor que enviará los comandos
#define COMMAND_SERVER_IP   "192.168.4.1"   // IP del otro ESP
#define COMMAND_SERVER_PORT 80              // Puerto del servidor
#define COMMAND_SERVER_PATH "/get_command"  // Ruta para pedir comandos
#define COMMAND_QUERY_INTERVAL_MS 500       // Tiempo en ms entre cada consulta de comando


// =================================================================
// ==               DEFINICIÓN DE COMANDOS HTTP                   ==
// =================================================================
#define CMD_AVANZAR         "AVANZAR"
#define CMD_DETENER         "DETENER"
#define CMD_REVERSA        "REVERSA"
#define CMD_GIRO_DERECHA   "GIRO_DERECHA"
#define CMD_GIRO_IZQUIERDA "GIRO_IZQUIERDA"

#endif // CONFIG_H
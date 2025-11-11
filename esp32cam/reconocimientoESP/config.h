#ifndef CONFIG_H
#define CONFIG_H

#include <WiFi.h>

// =================================================================
// ==           CONFIGURACIÓN DEL ACCESS POINT (AP)               ==
// =================================================================
#define AP_WIFI_SSID "ESP_AccessPoint"      // Nombre de la red que creará el ESP32
#define AP_WIFI_PASSWORD "12345678"     // Contraseña de la red
#define AP_SERVER_IP   192,168,4,1

#define AP_SERVER_PORT 80               // Puerto del servidor web
#define WEBSOCKET_PORT 81              // Puerto del servidor WebSocket
#define STREAM_PORT 82                 // Puerto para el servidor de streaming

// =================================================================
// ==               DEFINICIÓN DE COMANDOS                        ==
// =================================================================
#define CMD_AVANZAR         "AVANZAR"
#define CMD_DETENER         "DETENER"
#define CMD_REVERSA         "REVERSA"
#define CMD_GIRO_DERECHA    "GIRO_DERECHA"
#define CMD_GIRO_IZQUIERDA  "GIRO_IZQUIERDA"


// =================================================================
// ==      CONFIGURACIÓN DE PINES DE LA CÁMARA (ESP32-CAM)        ==
// =================================================================
#define CAMERA_MODEL_AI_THINKER

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// =================================================================
// ==                OTRAS sCONFIGURACIONES DE CAMARA              ==
// =================================================================
#define FRAME_SIZE FRAMESIZE_VGA    // Tamaño del frame (QVGA: 320x240 ; VGA: 640x480 ; SVGA: 800x600)
#define FRAME_QUALITY 10            // Calidad de la imagen (10-63, donde 10 es la mejor calidad)
#define FRAME_FB_COUNT 1            // Cantidad de frame buffers (Usar 2 para mayor fluidez, 1 para menos RAM)



#endif // CONFIG_H
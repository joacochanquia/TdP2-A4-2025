#include <WebServer.h>
#include <WebSocketsServer.h>
#include "config.h"
#include "WiFiHandler.h"
#include "control_webpage.h"
#include "main_webpage.h"

// Se crea una instancia del servidor en el puerto 80
static WebServer server(AP_SERVER_PORT);
// Instancia del servidor WebSocket en el puerto 81
static WebSocketsServer webSocket(WEBSOCKET_PORT);

// Variable estática para almacenar el último comando recibido
static String comandoActual = CMD_DETENER;

// --- Manejador de eventos WebSocket ---
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Cliente WebSocket desconectado.\n", num);
            break;
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Cliente WebSocket conectado desde %s\n", num, ip.toString().c_str());
            webSocket.sendTXT(num, "¡Conectado al ESP32!");
            break;
        }
        case WStype_TEXT:
            Serial.printf("[%u] Comando recibido: %s\n", num, payload);
            webSocket.broadcastTXT(payload, length);
            break;
    }
}

// --- Funciones internas de manejo de rutas (handlers) ---

// Maneja la ruta raíz ("/") para servir la página principal
static void handleRoot() {
  server.send(200, "text/html", HTML_MAIN_PAGE);
}

// Maneja la ruta "/control" para servir la página de control remoto
static void handleControl() {
  // Procesa comandos si se envían a esta página también
  if (server.hasArg("cmd")) {
    comandoActual = server.arg("cmd");
    Serial.print("Comando web recibido en /control: ");
    Serial.println(comandoActual);
  }
  server.send(200, "text/html", HTML_CONTROL_PAGE);
}

// Maneja las páginas no encontradas (404)
static void handleNotFound() {
  server.send(404, "text/plain", "404: Not Found");
}


// --- Implementación de las funciones públicas ---

void server_init() {
  IPAddress local_IP(AP_SERVER_IP);
  IPAddress gateway(AP_SERVER_IP);
  IPAddress subnet(255, 255, 255, 0);

  // Configura e inicia el Access Point
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_WIFI_SSID, AP_WIFI_PASSWORD);

  Serial.print("Access Point creado. SSID: ");
  Serial.println(AP_WIFI_SSID);
  Serial.print("IP del servidor: http://");
  Serial.println(WiFi.softAPIP());

  // Define las rutas y sus funciones de manejo
  server.on("/", HTTP_GET, handleRoot);
  server.on("/control", HTTP_GET, handleControl);
  server.onNotFound(handleNotFound);

  // Iniciar el servidor Web
  server.begin();
  Serial.println("Servidor HTTP iniciado.");

  // Iniciar el servidor WebSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("Servidor WebSocket iniciado.");
}

void server_handle_client() {
  server.handleClient();
  webSocket.loop();
}

void webSocket_broadcast(String message) {
  webSocket.broadcastTXT(message);
}
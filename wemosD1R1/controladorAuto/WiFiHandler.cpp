#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WebSocketsClient.h>
#include "config.h"
#include "WiFiHandler.h"
#include "webpage.h"

// Variable estática para guardar el modo actual de operación
static ModosOperacion modoActual;

// --- Variables y funciones solo para MODO AP ---
ESP8266WebServer server(80);
String receivedCommandAP = "";

void handleRoot() {
  if (server.hasArg("cmd")) {
    receivedCommandAP = server.arg("cmd");
  }
  server.send(200, "text/html", HTML_CONTENT);
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not Found");
}

// --- Variables solo para MODO CLIENTE ---
static WebSocketsClient webSocket;
static String commandFromWebSocket = "";

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("[WSc] Desconectado del servidor.");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Conectado al servidor: %s\n", payload);
      break;
    case WStype_TEXT:
      commandFromWebSocket = String((char*)payload);
      break;
  }
}

// --- Implementación de las funciones principales ---

ModosOperacion wifi_init() {
  // Configurar el pin de selección de modo con resistencia PULLUP interna.
  // Si el pin no está conectado, su estado será ALTO (HIGH).
  // Si se conecta a GND, su estado será BAJO (LOW).
  pinMode(MODE_PIN, INPUT_PULLUP);
  delay(10);

  if (digitalRead(MODE_PIN) == CLIENT_MODE_VALUE) {
    // ---- INICIAR EN MODO CLIENTE (STA) ----
modoActual = MODE_CLIENT;
    Serial.println("Iniciando en MODO CLIENTE (WebSocket)...");
    WiFi.begin(CLIENT_WIFI_SSID, CLIENT_WIFI_PASSWORD);
    
    Serial.print("Conectando a '");
    Serial.print(CLIENT_WIFI_SSID);
    Serial.print("'");

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConectado!");
    Serial.print("Dirección IP asignada: ");
    Serial.println(WiFi.localIP());

    // Configurar e iniciar el cliente WebSocket
    webSocket.begin(COMMAND_SERVER_IP, COMMAND_SERVER_PORT, "/");
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(5000);

  } else {
    // ---- INICIAR EN MODO ACCESS POINT (AP) ----
    modoActual = MODE_AP;
    Serial.println("Iniciando en MODO ACCESS POINT...");
    
    IPAddress local_IP(AP_SERVER_IP);
    IPAddress gateway(AP_SERVER_IP);
    IPAddress subnet(255, 255, 255, 0);

    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(AP_WIFI_SSID, AP_WIFI_PASSWORD);

    Serial.print("AP iniciado. Conectate a la red: ");
    Serial.println(AP_WIFI_SSID);
    Serial.print("IP del servidor: http://");
    Serial.println(WiFi.softAPIP());

    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("Servidor HTTP iniciado.");
  }

  return modoActual;
}

String wifi_get_command() {
  if (modoActual == MODE_AP) { // modo ACCESS POINT
    // En modo AP, escuchamos peticiones HTTP en nuestro servidor
    receivedCommandAP = "";
    server.handleClient();
    return receivedCommandAP;

  } else { // modo CLIENTE
    // En modo Cliente, escuchamos mensajes WebSocket del servidor
    webSocket.loop();
    if (commandFromWebSocket.length() > 0) {
      String cmd = commandFromWebSocket;
      commandFromWebSocket = "";
      return cmd; // Devolver el comando recibido
    }
    return "";
  }
}
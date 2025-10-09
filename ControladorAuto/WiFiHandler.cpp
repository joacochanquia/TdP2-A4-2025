#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "config.h"
#include "WiFiHandler.h"
#include "webpage.h"

// --- Variables para el servidor en MODO AP ---
ESP8266WebServer server(80);
String receivedCommandAP = "";

// --- Funciones para manejar las peticiones del servidor ---
void handleRoot() {
  if (server.hasArg("cmd")) {
    receivedCommandAP = server.arg("cmd");
  }
  server.send(200, "text/html", HTML_CONTENT);
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not Found");
}


// --- Implementación de las funciones principales ---

void wifi_init() {
  // ---- INICIAR EN MODO ACCESS POINT (AP) ----
  Serial.println("Iniciando en MODO ACCESS POINT...");
  
  IPAddress local_IP(AP_SERVER_IP);
  IPAddress gateway(AP_SERVER_IP);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_WIFI_SSID, AP_WIFI_PASSWORD);

  Serial.print("AP iniciado. Conéctate a la red: ");
  Serial.println(AP_WIFI_SSID);
  Serial.print("IP del servidor: http://");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Servidor HTTP iniciado.");
}

String wifi_get_command() {
  receivedCommandAP = "";
  server.handleClient();
  return receivedCommandAP;
}
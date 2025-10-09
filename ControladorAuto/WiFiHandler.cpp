#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> // Necesario para el modo cliente
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
unsigned long lastQueryTime = 0;

// --- Implementación de las funciones principales ---

ModosOperacion wifi_init() {
  // Configurar el pin de selección de modo con resistencia PULLUP interna.
  // Esto significa que si el pin no está conectado a nada, su estado será ALTO (HIGH).
  // Si lo conectas a GND, su estado será BAJO (LOW).
  pinMode(MODE_PIN, INPUT_PULLUP);
  delay(10); // Pequeña pausa para estabilizar la lectura del pin

  if (digitalRead(MODE_PIN) == CLIENT_MODE_VALUE) {
    // ---- INICIAR EN MODO CLIENTE (STA) ----
    modoActual = MODE_CLIENT;
    Serial.println("Pin de modo conectado a GND. Iniciando en MODO CLIENTE...");
    WiFi.begin(CLIENT_WIFI_SSID, CLIENT_WIFI_PASSWORD);
    
    Serial.print("Conectando a '");
    Serial.print(CLIENT_WIFI_SSID);
    Serial.print("'");

    // Esperar a que se establezca la conexión
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConectado!");
    Serial.print("Dirección IP asignada: ");
    Serial.println(WiFi.localIP());

  } else {
    // ---- INICIAR EN MODO ACCESS POINT (AP) ----
    modoActual = MODE_AP;
    Serial.println("Pin de modo no conectado. Iniciando en MODO ACCESS POINT...");
    
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

  return modoActual;
}

String wifi_get_command() {
  if (modoActual == MODE_AP) {
    // En modo AP, escuchamos peticiones HTTP en nuestro servidor
    receivedCommandAP = "";
    server.handleClient();
    return receivedCommandAP;

  } else { // modoActual == MODE_CLIENT
    // En modo Cliente, hacemos una petición a un servidor externo cada cierto intervalo
    if (millis() - lastQueryTime > COMMAND_QUERY_INTERVAL_MS) {
      lastQueryTime = millis(); // Actualizar el tiempo de la última consulta

      WiFiClient wifiClient;
      HTTPClient http;
      String command = "";
      
      String serverUrl = "http://" + String(COMMAND_SERVER_IP) + ":" + String(COMMAND_SERVER_PORT) + String(COMMAND_SERVER_PATH);

      if (http.begin(wifiClient, serverUrl)) {
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
          command = http.getString();
          command.trim(); // Limpiar espacios en blanco
        } else {
          Serial.printf("[HTTP] GET... falló, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
      } else {
        Serial.printf("[HTTP] No se pudo conectar\n");
      }
      return command;
    }
    return ""; // No ha pasado el intervalo, no devolvemos nada
  }
}
#include <WebServer.h>
#include "config.h"
#include "WiFiHandler.h"
#include "webpage.h"

// Se crea una instancia del servidor en el puerto 80
static WebServer server(80);

// Variable estática para almacenar el último comando recibido
static String comandoActual = CMD_DETENER;

// --- Funciones internas de manejo de rutas (handlers) ---

// Maneja la ruta raíz ("/") para servir la página y recibir comandos
static void handleRoot() {
  if (server.hasArg("cmd")) {
    comandoActual = server.arg("cmd");
    Serial.print("Comando web recibido: ");
    Serial.println(comandoActual);
  }
  server.send(200, "text/html", HTML_CONTENT);
}

// Maneja la ruta "/get_command" para que el Wemos consulte el comando
static void handleGetCommand() {
  Serial.print("Petición desde Wemos. Enviando: ");
  Serial.println(comandoActual);
  server.send(200, "text/plain", comandoActual);
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
  server.on("/get_command", HTTP_GET, handleGetCommand);
  server.onNotFound(handleNotFound);

  // Iniciar el servidor
  server.begin();
}

void server_handle_client() {
  server.handleClient();
}
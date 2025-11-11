#include "FS.h"
#include "SPIFFS.h"

void listSpiffsFiles() {
  Serial.println("Listando archivos en SPIFFS:");

  File root = SPIFFS.open("/");
  if (!root) {
    Serial.println("- No se pudo abrir el directorio raíz");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("- No es un directorio");
    return;
  }

  File file = root.openNextFile();
  int fileCount = 0;
  while (file) {
    if (file.isDirectory()) {
      Serial.printf("  DIR : %s\n", file.name());
    } else {
      Serial.printf("  FILE: %s  (Tamaño: %u bytes)\n", file.name(), file.size());
      fileCount++;
    }
    file = root.openNextFile();
  }
  
  if (fileCount == 0) {
    Serial.println("No se encontraron archivos en SPIFFS.");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- Prueba de SPIFFS ESP32-CAM ---");

  // Inicializar SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("¡Error al montar el sistema de archivos SPIFFS!");
    Serial.println("Asegúrate de haber seleccionado una 'Partition Scheme' (Esquema de Partición) que incluya SPIFFS.");
    return;
  }

  Serial.println("SPIFFS montado correctamente.");

  // Listar todos los archivos
  listSpiffsFiles();

  // --- Prueba de lectura de archivo ---
  Serial.println("\nIntentando leer el archivo /test.txt...");
  
  if (SPIFFS.exists("/test.txt")) {
    Serial.println("El archivo /test.txt existe.");
    File file = SPIFFS.open("/test.txt", "r");
    
    if (!file) {
      Serial.println("- Error al abrir el archivo para leer.");
    } else {
      Serial.println("Contenido del archivo:");
      while (file.available()) {
        Serial.write(file.read());
      }
      Serial.println();
      file.close();
      Serial.println("Lectura de archivo completa.");
    }
  } else {
    Serial.println("¡Error! El archivo /test.txt no fue encontrado.");
    Serial.println("Por favor, asegúrate de haber subido los datos (filesystem) correctamente.");
  }

  Serial.println("\n--- Fin de la prueba ---");
}

void loop() {
  delay(10000);
}
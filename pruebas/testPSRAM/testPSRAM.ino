#include "esp_camera.h"
#include "esp_heap_caps.h"

// Configuración para el modelo AI-THINKER ESP32-CAM
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

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("\n--- Prueba de PSRAM ESP32-CAM ---");

  // --- Importante: Habilitar PSRAM ---
  // Esta configuración habilita la PSRAM. 
  // En muchos cores de ESP32 para Arduino, la PSRAM se habilita 
  // automáticamente si la seleccionas en el menú "Tools" (Herramientas) 
  // de la IDE de Arduino (ej: "PSRAM: Enabled").
  // Si la PSRAM está habilitada por defecto en tu configuración de placa,
  // esta línea no es estrictamente necesaria, pero la dejamos para asegurar.
  
  // Nota: La inicialización de la cámara (esp_camera_init) también
  // inicializa y verifica la PSRAM si está configurada para usarla.
  // Pero para una prueba simple de PSRAM *antes* de la cámara, usamos heap_caps.

  if (!psramFound()) {
    Serial.println("Error: PSRAM no encontrada.");
    Serial.println("Verifica la configuración de tu placa en la IDE de Arduino.");
    return;
  }
  
  Serial.println("PSRAM encontrada!");

  // Imprimir tamaño total y libre de la PSRAM
  size_t totalPsram = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
  size_t freePsram = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);

  Serial.printf("Tamaño total PSRAM: %u bytes (%.2f MB)\n", totalPsram, totalPsram / (1024.0 * 1024.0));
  Serial.printf("PSRAM libre inicial: %u bytes (%.2f MB)\n", freePsram, freePsram / (1024.0 * 1024.0));

  // --- Prueba de asignación de memoria ---
  Serial.println("\nIntentando asignar 1MB (1 * 1024 * 1024 bytes) desde PSRAM...");
  
  // Usamos ps_malloc (o heap_caps_malloc con MALLOC_CAP_SPIRAM) 
  // para asignar memoria específicamente de la PSRAM.
  void* psramBuffer = heap_caps_malloc(1 * 1024 * 1024, MALLOC_CAP_SPIRAM);

  if (psramBuffer != NULL) {
    Serial.println("¡Éxito! Se asignó 1MB de PSRAM correctamente.");
    
    // Opcional: Escribir y leer datos para verificar
    Serial.println("Escribiendo y verificando datos en la PSRAM...");
    uint8_t* testData = (uint8_t*)psramBuffer;
    testData[0] = 0xAA; // Escribir al inicio
    testData[1024 * 1024 - 1] = 0x55; // Escribir al final
    
    if (testData[0] == 0xAA && testData[1024 * 1024 - 1] == 0x55) {
      Serial.println("Verificación de datos exitosa.");
    } else {
      Serial.println("Error en la verificación de datos.");
    }

    // Liberar la memoria asignada
    heap_caps_free(psramBuffer);
    Serial.println("Memoria PSRAM liberada.");
    
    size_t freePsramAfter = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    Serial.printf("PSRAM libre después de la prueba: %u bytes\n", freePsramAfter);

  } else {
    Serial.println("¡Fallo! No se pudo asignar 1MB de PSRAM.");
    Serial.println("Esto puede ocurrir si la PSRAM no está funcionando o si ya está en uso.");
  }

  Serial.println("\n--- Fin de la prueba ---");
  
  // Opcional: Si quieres probar la cámara después, puedes inicializarla aquí.
  // Serial.println("Inicializando cámara (esto también usa PSRAM)...");
  // initCamera();
}

void loop() {
  // No hacer nada en el loop para esta prueba
  delay(10000);
}


// --- Función de inicialización de cámara (Opcional) ---
// La dejamos aquí como referencia, ya que la inicialización 
// de la cámara es la principal consumidora de PSRAM.
esp_err_t initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; // Formato JPEG

  // Configuración para alta resolución (UXGA) - Requiere PSRAM
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA; // 1600x1200
    config.jpeg_quality = 10; // 0-63 (menor = mayor calidad)
    config.fb_count = 2; // Usar 2 frame buffers en PSRAM
    config.fb_location = CAMERA_FB_IN_PSRAM; // Forzar uso de PSRAM
  } else {
    // Configuración de baja resolución si no hay PSRAM
    config.frame_size = FRAMESIZE_SVGA; // 800x600
    config.jpeg_quality = 12;
    config.fb_count = 1;
    config.fb_location = CAMERA_FB_IN_DRAM;
  }

  // Inicializar la cámara
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Fallo al inicializar la cámara: 0x%x\n", err);
    return err;
  }

  Serial.println("Cámara inicializada correctamente.");
  return ESP_OK;
}
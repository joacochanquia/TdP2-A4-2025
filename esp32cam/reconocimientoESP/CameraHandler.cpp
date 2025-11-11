#include "CameraHandler.h"
#include "config.h" // Para los pines de la cámara
#include "WiFi.h" // Para Serial

// Includes para la Cámara y el Servidor de Streaming
#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_timer.h"
#include "WiFiHandler.h" 

// --- Lógica del Servidor de Streaming (en puerto 82) ---

// Definición del tipo de handler
typedef esp_err_t (*httpd_req_handler_t)(httpd_req_t *r);


static httpd_handle_t stream_httpd = NULL;

// --- Variables para cálculo de FPS ---
static unsigned long lastFPSTime = 0;
static int frameCount = 0;

// Manejador para el stream de video
static esp_err_t stream_handler(httpd_req_t *req){
  camera_fb_t * fb = NULL;
  esp_err_t res = ESP_OK;
  size_t _jpg_buf_len;
  uint8_t * _jpg_buf;
  char * part_buf[64];
  
  res = httpd_resp_set_type(req, "multipart/x-mixed-replace;boundary=--frame");
  if(res != ESP_OK){
    return res;
  }
  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");

  // Reseteamos el contador cada vez que un cliente nuevo se conecta
  lastFPSTime = millis();
  frameCount = 0;

  while(true){
    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Fallo al capturar frame");
      res = ESP_FAIL;
      break;
    }
    if(fb->format != PIXFORMAT_JPEG){
      Serial.println("Formato no es JPEG");
      res = ESP_FAIL;
    } else {
      _jpg_buf_len = fb->len;
      _jpg_buf = fb->buf;
    }
    
    if(res == ESP_OK){
      size_t hlen = snprintf((char *)part_buf, 64, 
                             "--frame\r\n"
                             "Content-Type: image/jpeg\r\n"
                             "Content-Length: %u\r\n\r\n", 
                             _jpg_buf_len);
      res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
    }
    if(res == ESP_OK){
      res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
      if (res == ESP_OK) {
        res = httpd_resp_send_chunk(req, "\r\n", 2);
      }
    }
    
    esp_camera_fb_return(fb);
    if(res != ESP_OK){
      break;
    }


    // Contador de FPS
    frameCount++;
    unsigned long currentTime = millis();
    if (currentTime - lastFPSTime >= 1000) {
      Serial.printf("FPS: %d\n", frameCount);
      String fpsStr = "FPS:" + String(frameCount);
      frameCount = 0;
      lastFPSTime = currentTime;
      webSocket_broadcast(fpsStr); // Enviar "FPS:XX" por WebSocket
    }
  }
  return res;
}

// Función para iniciar el servidor de streaming en el puerto 82
static void startCameraServer(){
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = STREAM_PORT; // Puerto 82
  config.ctrl_port = 32768; // Puerto de control
  config.stack_size = 8192; // Aumentar stack size

  httpd_uri_t stream_uri = {
    .uri       = "/stream",
    .method    = HTTP_GET,
    .handler   = stream_handler,
    .user_ctx  = NULL
  };

  Serial.printf("Iniciando servidor de stream en puerto: '%d'\n", config.server_port);
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &stream_uri);
  }
}

// --- Configuración de la Cámara ---
static void setupCamera() {
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
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; 
  
  // Configuración para baja latencia y alta velocidad
  config.frame_size = FRAME_SIZE; // FRAMESIZE_QVGA o FRAMESIZE_VGA. VGA es 640x480
  config.jpeg_quality = FRAME_QUALITY; // 10-63 (menor = mayor calidad)
  config.fb_count = FRAME_FB_COUNT; // Usar 2 para mayor fluidez, 1 para menos RAM
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;

  // Inicializar la cámara
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Error al inicializar la cámara: 0x%x\n", err);
    return;
  }
  Serial.println("Cámara inicializada correctamente.");

  // Configuración adicional del sensor
  sensor_t * s = esp_camera_sensor_get();
  s->set_vflip(s, 1); // Voltear verticalmente
  s->set_hmirror(s, 1); // Espejo horizontal
}


// --- Función Pública ---

void setup_camera_handler() {
  setupCamera();
  startCameraServer();
}
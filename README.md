# TdP2-A4-2025 - Proyecto MediaPipe

Este proyecto implementa diferentes aplicaciones de reconocimiento de gestos y detección de manos utilizando MediaPipe y OpenCV. El proyecto está organizado en tres módulos principales, cada uno con funcionalidades específicas para el procesamiento de imágenes y reconocimiento de gestos en tiempo real.

## 🏗️ Estructura del Proyecto

```
TdP2-A4-2025/
├── README.md
├── LevantarDocker.txt
├── ArchivosMediapipe/
│   └── gesture_recognizer.ipynb     # Notebook de ejemplo de MediaPipe
├── mediapipe_cameraAndPoints/       # Detección de puntos de mano
│   ├── app.py
│   ├── Dockerfile
│   ├── rebuild.sh
│   └── requirements.txt
├── mediapipe_gesture/               # Reconocimiento de gestos
│   ├── app.py
│   ├── Dockerfile
│   ├── gesture_recognizer.task
│   ├── rebuild.sh
│   └── requirements.txt
└── mediapipe_gestureAndPoints/      # Gestos + puntos combinados
    ├── app.py
    ├── Dockerfile
    ├── gesture_recognizer.task
    ├── rebuild.sh
    └── requirements.txt
```

## 📋 Módulos del Proyecto

### 1. **mediapipe_cameraAndPoints**
- **Funcionalidad**: Detección y visualización de puntos de referencia de las manos
- **Características**:
  - Captura video en tiempo real desde la cámara
  - Detecta hasta 21 puntos de referencia por mano
  - Dibuja las conexiones entre los puntos detectados
  - Visualización en tiempo real de la estructura de la mano

### 2. **mediapipe_gesture**
- **Funcionalidad**: Reconocimiento de gestos predefinidos
- **Características**:
  - Reconoce 7 gestos de mano: 👍, 👎, ✌️, ☝️, ✊, 👋, 🤟
  - Muestra el gesto detectado con su puntuación de confianza
  - Utiliza modelo preentrenado de Google MediaPipe
  - Procesamiento en tiempo real

### 3. **mediapipe_gestureAndPoints**
- **Funcionalidad**: Combinación de detección de puntos y reconocimiento de gestos
- **Características**:
  - Detecta y dibuja puntos de referencia de las manos
  - Reconoce gestos simultáneamente
  - Visualización completa con puntos, conexiones y etiquetas de gestos
  - Mayor precisión en la detección

## 🔧 Requisitos del Sistema

- **Python**: 3.10 o superior
- **Dependencias**:
  - `mediapipe`
  - `opencv-python`
- **Hardware**:
  - Cámara web conectada
  - Sistema compatible con OpenCV (Linux, Windows, macOS)

## 🚀 Instalación y Uso

### Opción 1: Ejecución Local

1. **Clonar el repositorio**:
   ```bash
   git clone <url-del-repositorio>
   cd TdP2-A4-2025
   ```

2. **Instalar dependencias** (para cualquier módulo):
   ```bash
   cd mediapipe_cameraAndPoints  # o el módulo que desees
   pip install -r requirements.txt
   ```

3. **Ejecutar la aplicación**:
   ```bash
   python app.py
   ```

### Opción 2: Ejecución con Docker

1. **Construir la imagen Docker**:
   ```bash
   cd mediapipe_gesture  # o el módulo que desees
   docker build -t mediapipe-app .
   ```

2. **Ejecutar el contenedor** (Linux/macOS):
   ```bash
   docker run -it --rm \
       --device /dev/video0:/dev/video0 \
       -e DISPLAY=$DISPLAY \
       -v /tmp/.X11-unix:/tmp/.X11-unix \
       mediapipe-app
   ```

### Script de Reconstrucción

Cada módulo incluye un script `rebuild.sh` para facilitar la reconstrucción:
```bash
chmod +x rebuild.sh
./rebuild.sh
```

## 🎮 Controles

- **ESC**: Salir de la aplicación
- **Ventana**: Cierra la aplicación al cerrar la ventana

## 🤖 Gestos Reconocidos

El modelo preentrenado puede reconocer los siguientes gestos:

| Gesto | Descripción |
|-------|-------------|
| 👍 | Pulgar arriba |
| 👎 | Pulgar abajo |
| ✌️ | Victoria/Paz |
| ☝️ | Índice señalando |
| ✊ | Puño cerrado |
| 👋 | Saludo/Adiós |
| 🤟 | Te amo (ASL) |

## 📚 Recursos Adicionales

- **Notebook**: `ArchivosMediapipe/gesture_recognizer.ipynb` contiene ejemplos y documentación adicional de MediaPipe
- **Modelo**: `gesture_recognizer.task` es el modelo preentrenado de Google para reconocimiento de gestos

## 🛠️ Solución de Problemas

### Problemas Comunes

1. **Cámara no detectada**:
   - Verificar que la cámara esté conectada
   - Cambiar el índice de cámara en `cv2.VideoCapture(0)` por `1`, `2`, etc.

2. **Error de permisos con Docker**:
   ```bash
   sudo xhost +local:docker  # Permitir acceso a X11
   ```

3. **Dependencias faltantes**:
   ```bash
   sudo apt-get install ffmpeg libsm6 libxext6 libgl1  # Ubuntu/Debian
   ```

## 🎯 Casos de Uso

- **Educación**: Aprendizaje de visión por computadora y MediaPipe
- **Prototipado**: Base para aplicaciones de interfaz gestual
- **Investigación**: Análisis de movimientos de mano
- **Accesibilidad**: Desarrollo de interfaces controladas por gestos

## 🤝 Contribuciones

Este proyecto es parte del curso TdP2 (Taller de Proyecto 2) y está abierto a mejoras y contribuciones.

## 📄 Licencia

Este proyecto utiliza MediaPipe de Google, que está licenciado bajo Apache License 2.0.


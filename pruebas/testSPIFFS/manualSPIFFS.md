# **Manual: Cargar Archivos SPIFFS en Arduino IDE 2.0+**

Este manual explica cómo instalar y usar la herramienta "ESP32 Sketch Data Upload" en la versión 2.0 (y superiores) de la IDE de Arduino, ya que no viene preinstalada.

## **Paso 1: Instalar la Herramienta**

La herramienta ahora se distribuye como un archivo ZIP que debes colocar en la carpeta tools de tu Sketchbook de Arduino.

1. **Cierra completamente** la IDE de Arduino 2.0.  
2. **Encuentra tu carpeta "Sketchbook"**:  
   * Abre la IDE de Arduino (temporalmente si la cerraste) y ve a File \> Preferences... (o Archivo \> Preferencias...).  
   * Mira la ruta en "Sketchbook location" (Ubicación del cuaderno de bocetos). Por lo general, es C:\\Users\\\[TuUsuario\]\\Documents\\Arduino.  
   * Ve a esa carpeta en el explorador de archivos de tu sistema.  
3. **Crea la carpeta tools**:  
   * Dentro de tu carpeta de Sketchbook (ej: Documents\\Arduino), crea una nueva carpeta llamada exactamente tools (todo en minúsculas), si es que no existe ya.  
4. **Descarga la Herramienta**:  
   * Ve a la página oficial de "releases" (lanzamientos) del paquete de Arduino ESP32:  
     https://github.com/lorol/arduino-esp32fs-plugin/releases
   * Busca la versión más reciente (la de arriba, marcada como "Latest").  
   * En la sección "Assets", descarga el archivo llamado ESP32.Tools.zip.  
5. **Descomprime la Herramienta**:  
   * Mueve el archivo ESP32.Tools.zip que acabas de descargar a la carpeta tools que creaste en el paso 3\.  
   * Descomprime el archivo ZIP **directamente dentro** de la carpeta tools.  
   * La estructura de carpetas final debería verse así:  
     Documents/  
     └── Arduino/  
         ├── libraries/  
         ├── sketches/  
         └── tools/  
             └── ESP32Tools/  \<-- (Esta carpeta viene de descomprimir el ZIP)  
                 ├── tool/  
                 │   └── esp32fs.jar  
                 └── ... (otros archivos)

6. **Reinicia la IDE de Arduino 2.0**: Vuelve a abrir la IDE.

¡Listo\! Ahora, si vas al menú Tools (Herramientas), deberías ver una nueva opción llamada ESP32 Sketch Data Upload.

## **Paso 2: Preparar y Subir los Archivos**

1. **Abre el Sketch de Prueba**: Abre el archivo testSPIFFS.ino.  
2. **Crea la carpeta data**:  
   * En la misma carpeta donde está tu archivo .ino, crea una nueva carpeta llamada exactamente data (todo en minúsculas).  
3. **Crea el archivo de prueba**:  
   * Dentro de la carpeta data, crea un nuevo archivo de texto llamado test.txt.  
   * Ábrelo y escribe un mensaje, por ejemplo: ¡Hola SPIFFS desde la ESP32-CAM\!  
   * Guarda el archivo.  
   * La estructura de tu sketch debe ser:  
     testSPIFFS/  
     ├── testSPIFFS.ino  
     └── data/  
         └── test.txt

4. **Configura la IDE para la Subida**:  
   * En la IDE de Arduino, asegúrate de tener seleccionada tu placa (ej: "AI Thinker ESP32-CAM").  
   * Selecciona el puerto COM correcto.  
   * **¡MUY IMPORTANTE\!** Ve a Tools \> Partition Scheme (Esquema de Partición). Asegúrate de seleccionar una opción que incluya SPIFFS (por ejemplo: "Default 4MB with SPIFFS (1.2MB APP/1.5MB SPIFFS)"). Si eliges una partición sin SPIFFS, la subida fallará.  
5. **Sube los Datos**:  
   * Pon tu ESP32-CAM en modo de flasheo (generalmente, mantén presionado IO0 y presiona RESET).  
   * Ve a Tools \> ESP32 Sketch Data Upload.  
   * Espera a que la consola muestre "SPIFFS Image Uploaded".

## **Paso 3: Probar el Funcionamiento**

1. **Sube el Código**: Ahora, sube el sketch testSPIFFS.ino de la forma habitual (botón "Upload").  
2. **Abre el Monitor Serie**: Configura la velocidad a 115200 baudios.  
3. **Revisa la Salida**: Si todo funcionó, deberías ver algo como esto:  
   \--- Prueba de SPIFFS ESP32-CAM \---  
   SPIFFS montado correctamente.  
   Listando archivos en SPIFFS:  
     FILE: /test.txt  (Tamaño: 33 bytes)

   Intentando leer el archivo /test.txt...  
   El archivo /test.txt existe.  
   Contenido del archivo:  
   ¡Hola SPIFFS desde la ESP32-CAM\!  
   Lectura de archivo completa.

   \--- Fin de la prueba \---  

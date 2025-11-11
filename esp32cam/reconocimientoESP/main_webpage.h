#ifndef MAIN_WEBPAGE_H
#define MAIN_WEBPAGE_H

const char HTML_MAIN_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Control por Gestos</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap" rel="stylesheet">
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { font-family: 'Inter', sans-serif; background: #450920; color: #450920; min-height: 100vh; padding: 20px; }
        .main-container { max-width: 1400px; margin: 0 auto; background: rgba(255, 255, 255, 0.95); border-radius: 20px; box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1); backdrop-filter: blur(10px); overflow: hidden; }
        .header { background: #A53860; color: #F9DBBD; padding: 15px 20px; text-align: center; }
        .header h1 { font-size: 1.8rem; font-weight: 600; margin-bottom: 5px; text-shadow: 0 2px 4px rgba(0, 0, 0, 0.3); letter-spacing: -0.02em; }
        .content { display: flex; gap: 20px; padding: 20px; min-height: 500px; }
        .video-section { flex: 1; display: flex; flex-direction: column; align-items: center; }
        #video-container { position: relative; width: 100%; max-width: 600px; height: 400px; border: none; border-radius: 15px; overflow: hidden; background-color: #000; box-shadow: 0 10px 30px rgba(0, 0, 0, 0.3); margin-bottom: 15px; }
        
        #video-stream { width: 100%; height: 100%; object-fit: cover; display: block; background-color: #000; } 
        
        /* --- NUEVO: Estilo para el contador de FPS --- */
        #fps-counter {
            position: absolute;
            top: 10px;
            left: 10px;
            background: rgba(0, 0, 0, 0.5);
            color: white;
            padding: 5px 10px;
            border-radius: 5px;
            font-size: 0.9rem;
            font-weight: 500;
            z-index: 10;
            font-family: monospace;
        }
        
        #canvas { position: absolute; top: 0; left: 0; width: 100%; height: 100%; pointer-events: none; }
        .gesture-display { background: #f9c5cf; color: #450920; padding: 12px 20px; border-radius: 12px; text-align: center; box-shadow: 0 8px 25px rgba(165, 56, 96, 0.3); width: 100%; display: flex; align-items: center; justify-content: center; gap: 15px; }
        .gesture-display h2 { font-size: 1rem; margin: 0; font-weight: 500; letter-spacing: 0.025em; text-transform: uppercase; }
        #gesture-status { font-size: 1.4rem; font-weight: 600; text-shadow: 0 2px 4px rgba(0, 0, 0, 0.3); letter-spacing: -0.01em; margin: 0; }
        .instructions-section { flex: 1; display: flex; flex-direction: column; }
        .instructions-section h2 { color: #A53860; font-size: 1.4rem; margin-bottom: 15px; text-align: center; font-weight: 600; letter-spacing: -0.02em; }
        #info-container { background: #f9e0c7; border-radius: 12px; padding: 20px; box-shadow: 0 10px 25px rgba(165, 56, 96, 0.15); height: fit-content; border: 1px solid rgba(255, 165, 171, 0.3); }
        .instructions ul { list-style: none; padding: 0; }
        .instructions li { background: rgba(255, 255, 255, 0.9); margin-bottom: 10px; padding: 12px 15px; border-radius: 8px; box-shadow: 0 2px 8px rgba(69, 9, 32, 0.1); border-left: 4px solid #A53860; transition: transform 0.2s ease, box-shadow 0.2s ease; font-weight: 400; font-size: 0.9rem; line-height: 1.4; color: #450920; }
        .instructions li:hover { transform: translateY(-2px); box-shadow: 0 6px 15px rgba(69, 9, 32, 0.15); }
        .instructions li strong { color: #A53860; font-weight: 600; }
        .note { background: #f9cac5; padding: 12px 15px; border-radius: 8px; margin-top: 15px; border-left: 4px solid #DA627D; box-shadow: 0 2px 8px rgba(165, 56, 96, 0.1); font-size: 0.85rem; line-height: 1.4; color: #450920; }
        .note strong { color: #A53860; font-weight: 600; }
        @media (max-width: 1024px) { .content { flex-direction: column; } .header h1 { font-size: 2rem; } #video-container { max-width: 100%; height: 400px; } }
        @media (max-width: 768px) { .main-container { margin: 10px; border-radius: 15px; } .content { padding: 20px; gap: 20px; } .header { padding: 20px; } .header h1 { font-size: 1.8rem; } #video-container { height: 300px; } }
    </style>
</head>
<body>
    <div class="main-container">
        <div class="header"><h1>Control Robótico por Gestos 👋</h1></div>
        <div class="content">
            <div class="video-section">
                <div id="video-container">
                    <div id="fps-counter">FPS: --</div>
                    
                    <img id="video-stream" src="http://192.168.4.1:82/stream">
                    <canvas id="canvas"></canvas>
                </div>
                <div class="gesture-display">
                    <h2>Gesto Reconocido:</h2>
                    <div id="gesture-status">Esperando conexión...</div>
                </div>
            </div>
            <div class="instructions-section">
                <!-- ... (sin cambios en esta sección) ... -->
                <h2>Instrucciones de Uso</h2>
                <div id="info-container">
                    <div class="instructions">
                        <ul>
                            <li>👆 <strong>Dedo Índice Arriba:</strong> El auto avanza</li>
                            <li>🖐️ <strong>Mano Abierta:</strong> El auto se detiene</li>
                            <li>✊ <strong>Puño Cerrado:</strong> El auto retrocede</li>
                            <li>👍 <strong>Pulgar Arriba:</strong> Gira a la derecha</li>
                            <li>👎 <strong>Pulgar Abajo:</strong> Gira a la izquierda</li>
                        </ul>
                    </div>
                    <div class="note"><strong>💡 Nota:</strong> Asegúrate de que la mano esté bien iluminada y completamente visible en el encuadre de la cámara para un mejor reconocimiento.</div>
                </div>
            </div>
        </div>
    </div>
    <script>
        const gestureStatus = document.getElementById('gesture-status');
        const fpsCounter = document.getElementById('fps-counter');
        
        const websocket = new WebSocket(`ws://192.168.4.1:81/`);

        websocket.onopen = function(event) {
            console.log("Conexión WebSocket establecida.");
            gestureStatus.textContent = "Conectado";
        };

        websocket.onmessage = function(event) {
            console.log("Mensaje recibido: " + event.data);

            if (event.data.startsWith("FPS:")) {
                // Si el mensaje empieza con "FPS:", es un contador de FPS
                fpsCounter.textContent = "FPS: " + event.data.substring(4); // Quita el prefijo "FPS:"
            } else {
                // De lo contrario, es un mensaje de gesto
                gestureStatus.textContent = event.data;
            }
        };
        
        websocket.onclose = function(event) {
            console.log("Conexión WebSocket cerrada.");
            gestureStatus.textContent = "Desconectado";
            fpsCounter.textContent = "FPS: --"; // Reseteamos el contador
        };
        websocket.onerror = function(error) {
            console.log("Error de WebSocket: " + error);
            gestureStatus.textContent = "Error de conexión";
            fpsCounter.textContent = "FPS: --";
        };
    </script>
</body>
</html>
)=====";

#endif // MAIN_WEBPAGE_H
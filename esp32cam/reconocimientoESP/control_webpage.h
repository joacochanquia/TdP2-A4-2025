#ifndef CONTROL_WEBPAGE_H
#define CONTROL_WEBPAGE_H

const char HTML_CONTROL_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="es">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no">
        <title>Control Auto Wemos</title>
        <style>
            html,body{height:100%;margin:0;display:flex;flex-direction:column;justify-content:center;align-items:center;background-color:#1e1e1e;color:#ecf0f1;font-family:sans-serif;touch-action:manipulation}h1{margin-bottom:2rem;font-size:2rem;text-align:center}.control-panel{display:grid;grid-template-columns:repeat(3,1fr);grid-template-rows:repeat(3,1fr);gap:15px;width:90vw;max-width:300px;height:90vw;max-height:300px}.control-button{display:flex;justify-content:center;align-items:center;border-radius:12px;font-size:2.5rem;color:#ecf0f1;cursor:pointer;user-select:none;transition:background-color .2s ease,transform .1s ease}.control-button:active{transform:scale(.95)}#forward{grid-area:1 / 2 / 2 / 3}#left{grid-area:2 / 1 / 3 / 2}#stop{grid-area:2 / 2 / 3 / 3}#right{grid-area:2 / 3 / 3 / 4}#reverse{grid-area:3 / 2 / 4 / 3}.direction-btn{background-color:#2980b9}.direction-btn:active{background-color:#3498db}#stop{background-color:#c0392b;font-size:1.5rem;font-weight:700}#stop:active{background-color:#e74c3c}
        </style>
    </head>
    <body>
        <h1>Control Auto Wemos</h1>
        <div class="control-panel">
            <div id="forward" class="control-button direction-btn" onmousedown="sendCommand('AVANZAR')" onmouseup="sendCommand('DETENER')" ontouchstart="event.preventDefault();sendCommand('AVANZAR')" ontouchend="sendCommand('DETENER')">&#8679;</div>
            <div id="left" class="control-button direction-btn" onmousedown="sendCommand('GIRO_IZQUIERDA')" onmouseup="sendCommand('DETENER')" ontouchstart="event.preventDefault();sendCommand('GIRO_IZQUIERDA')" ontouchend="sendCommand('DETENER')">&#8678;</div>
            <div id="stop" class="control-button" onclick="sendCommand('DETENER')">STOP</div>
            <div id="right" class="control-button direction-btn" onmousedown="sendCommand('GIRO_DERECHA')" onmouseup="sendCommand('DETENER')" ontouchstart="event.preventDefault();sendCommand('GIRO_DERECHA')" ontouchend="sendCommand('DETENER')">&#8680;</div>
            <div id="reverse" class="control-button direction-btn" onmousedown="sendCommand('REVERSA')" onmouseup="sendCommand('DETENER')" ontouchstart="event.preventDefault();sendCommand('REVERSA')" ontouchend="sendCommand('DETENER')">&#8681;</div>
        </div>
        <script>
            const websocket = new WebSocket(`ws://${window.location.hostname}:81/`);
            websocket.onopen = () => console.log("Conexión WebSocket establecida.");
            websocket.onclose = () => console.log("Conexión WebSocket cerrada.");
            websocket.onerror = (error) => console.log("Error de WebSocket: " + error);

            function sendCommand(command) {
                if (websocket.readyState === WebSocket.OPEN) {
                    websocket.send(command);
                } else {
                    console.log("WebSocket no está conectado.");
                }
            }
        </script>
    </body>
</html>
)=====";

#endif // CONTROL_WEBPAGE_H
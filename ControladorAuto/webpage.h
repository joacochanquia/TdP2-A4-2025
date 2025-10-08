#ifndef WEBPAGE_H
#define WEBPAGE_H

// Guardamos todo el HTML en una constante de tipo PROGMEM para ahorrar RAM
const char HTML_CONTENT[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Control Auto Wemos</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: Arial, sans-serif; text-align: center; background-color: #282c34; color: white; }
        .title { margin-top: 20px; font-size: 2.5em; }
        .container { display: flex; justify-content: center; align-items: center; margin-top: 30px; }
        .grid-container { display: grid; grid-template-columns: 1fr 1fr 1fr; grid-template-rows: 1fr 1fr 1fr; gap: 10px; width: 300px; height: 300px; }
        .btn {
            background-color: #61afef; color: white; border: none; border-radius: 10px;
            font-size: 2em; cursor: pointer; user-select: none;
            display: flex; justify-content: center; align-items: center;
            transition: background-color 0.2s;
        }
        .btn:active { background-color: #4a8ac1; }
        #btn-fwd { grid-column: 2; grid-row: 1; }
        #btn-left { grid-column: 1; grid-row: 2; }
        #btn-stop { grid-column: 2; grid-row: 2; background-color: #e06c75; }
        #btn-stop:active { background-color: #c04c55; }
        #btn-right { grid-column: 3; grid-row: 2; }
        #btn-rev { grid-column: 2; grid-row: 3; }
    </style>
</head>
<body>
    <div class="title">Control Auto Wemos</div>
    <div class="container">
        <div class="grid-container">
            <div id="btn-fwd" class="btn" onmousedown="sendCommand('AVANZAR')" onmouseup="sendCommand('DETENER')" ontouchstart="sendCommand('AVANZAR')" ontouchend="sendCommand('DETENER')">&#8593;</div>
            <div id="btn-left" class="btn" onmousedown="sendCommand('GIRO_IZQUIERDA')" onmouseup="sendCommand('DETENER')" ontouchstart="sendCommand('GIRO_IZQUIERDA')" ontouchend="sendCommand('DETENER')">&#8592;</div>
            <div id="btn-stop" class="btn" onclick="sendCommand('DETENER')">STOP</div>
            <div id="btn-right" class="btn" onmousedown="sendCommand('GIRO_DERECHA')" onmouseup="sendCommand('DETENER')" ontouchstart="sendCommand('GIRO_DERECHA')" ontouchend="sendCommand('DETENER')">&#8594;</div>
            <div id="btn-rev" class="btn" onmousedown="sendCommand('REVERSA')" onmouseup="sendCommand('DETENER')" ontouchstart="sendCommand('REVERSA')" ontouchend="sendCommand('DETENER')">&#8595;</div>
        </div>
    </div>
    <script>
        function sendCommand(command) {
            fetch('/?cmd=' + command);
        }
    </script>
</body>
</html>
)rawliteral";

#endif // WEBPAGE_H
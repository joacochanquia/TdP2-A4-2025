import cv2
import mediapipe as mp

# Importar GestureRecognizer
from mediapipe.tasks import python
from mediapipe.tasks.python import vision

# Ruta al modelo preentrenado de gestos (lo baja Google)
MODEL_PATH = "gesture_recognizer.task"

# Cargar modelo
base_options = python.BaseOptions(model_asset_path=MODEL_PATH)
options = vision.GestureRecognizerOptions(base_options=base_options)
recognizer = vision.GestureRecognizer.create_from_options(options)

# Captura de cámara
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Convertir a formato MediaPipe
    mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=frame)

    # Ejecutar reconocimiento
    result = recognizer.recognize(mp_image)

    # Mostrar gestos detectados
    if result.gestures:
        for gesture in result.gestures:
            category = gesture[0].category_name
            score = gesture[0].score
            cv2.putText(frame, f"{category} ({score:.2f})", (50, 50),
                        cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    # Mostrar cámara
    cv2.imshow("MediaPipe Gesture Recognizer", frame)
    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()

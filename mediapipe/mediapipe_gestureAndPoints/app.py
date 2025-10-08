import cv2
import mediapipe as mp
from mediapipe.tasks import python
from mediapipe.tasks.python import vision
from mediapipe.framework.formats import landmark_pb2

# Ruta al modelo
MODEL_PATH = "gesture_recognizer.task"

# Configuración del modelo
base_options = python.BaseOptions(model_asset_path=MODEL_PATH)
options = vision.GestureRecognizerOptions(base_options=base_options)
recognizer = vision.GestureRecognizer.create_from_options(options)

# Utilidades de dibujo
mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands

# Captura de cámara
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Convertir a RGB para MediaPipe
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=rgb_frame)

    # Ejecutar reconocimiento
    result = recognizer.recognize(mp_image)

    # Dibujar landmarks si existen
    if result.hand_landmarks:
        for hand_landmarks in result.hand_landmarks:
            # Convertir cada punto al tipo esperado por drawing_utils
            landmark_list = landmark_pb2.NormalizedLandmarkList()
            for lm in hand_landmarks:
                landmark = landmark_pb2.NormalizedLandmark(
                    x=lm.x,
                    y=lm.y,
                    z=lm.z
                )
                landmark_list.landmark.append(landmark)

            # Dibujar sobre el frame
            mp_drawing.draw_landmarks(
                frame,
                landmark_list,
                mp_hands.HAND_CONNECTIONS,
                mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=2, circle_radius=3),
                mp_drawing.DrawingSpec(color=(255, 0, 0), thickness=2, circle_radius=2),
            )

    # Mostrar gesto detectado
    if result.gestures:
        gesture_name = result.gestures[0][0].category_name
        score = result.gestures[0][0].score
        cv2.putText(frame, f"{gesture_name} ({score:.2f})", (30, 50),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    # Mostrar frame
    cv2.imshow("MediaPipe Gesture Recognizer", frame)
    if cv2.waitKey(1) & 0xFF == 27:  # ESC para salir
        break

cap.release()
cv2.destroyAllWindows()

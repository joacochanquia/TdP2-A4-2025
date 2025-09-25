#!/bin/bash

# Nombre de la imagen
IMAGE_NAME="mediapipe-app"

echo "🗑️ Eliminando contenedores viejos..."
docker ps -a -q --filter "ancestor=$IMAGE_NAME" | xargs -r docker rm -f

echo "🗑️ Eliminando imagen vieja..."
docker rmi -f $IMAGE_NAME

echo "🔨 Construyendo nueva imagen..."
docker build -t $IMAGE_NAME .

echo "🚀 Ejecutando contenedor..."
xhost +local:docker

docker run -it --rm \
    --device /dev/video0:/dev/video0 \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    $IMAGE_NAME

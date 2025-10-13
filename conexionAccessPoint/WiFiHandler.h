#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

// Inicializa el modo Access Point y el servidor web con sus rutas
void server_init();

// Escucha y procesa las peticiones de clientes HTTP
void server_handle_client();

#endif // WIFI_HANDLER_H
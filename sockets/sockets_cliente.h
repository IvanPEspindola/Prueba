#ifndef SOCKETS_CLIENTE_H_
#define SOCKETS_CLIENTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include "utils.h"

typedef struct
{
	e_operation_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

int crear_conexion_cliente(char *ip, char* puerto);
void enviar_mensaje(e_operation_code op_code, char* mensaje, int socket_cliente);
void enviar_handshake(int socket_cliente, e_proceso proceso);
t_paquete* crear_paquete(void);
t_paquete* crear_super_paquete(void);
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void enviar_paquete(t_paquete* paquete, int socket_cliente);
void liberar_conexion(int socket_cliente);
void eliminar_paquete(t_paquete* paquete);

#endif /* SOCKETS__CLIENTEH_ */

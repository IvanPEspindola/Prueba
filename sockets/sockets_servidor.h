#ifndef SOCKETS_SERVIDOR_H_
#define SOCKETS_SERVIDOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <string.h>
#include "utils.h"

t_log* logger;

void* recibir_buffer(int*, int);

int iniciar_servidor(char* ip, char* puerto);
int esperar_cliente(int socket);
e_proceso recibir_handshake(int socket);
t_list* recibir_paquete(int socket);
char* recibir_mensaje(int socket);
int recibir_operacion(int socket);

#endif /* SOCKETS_SERVIDOR_H_ */

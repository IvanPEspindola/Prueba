#include "sockets_servidor.h"

void* recibir_buffer(int*, int);

int iniciar_servidor(char* ip, char* puerto) {
	logger_servidor = log_create("log_servidor.log", "Servidor", 1, LOG_LEVEL_DEBUG);
	int socket_servidor;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(ip, puerto, &hints, &servinfo);

    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;

        if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
        	log_error(logger_servidor, "Error al hacer bind");
        	log_error(logger_servidor, strerror(errno));
            close(socket_servidor);
            continue;
        }
        break;
    }

	listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);

    log_trace(logger_servidor, "Listo para escuchar a mi cliente");

    return socket_servidor;
}

int esperar_cliente(int socket_servidor) {
	struct sockaddr dir_cliente;
	socklen_t tam_direccion = sizeof(struct sockaddr);
	int socket_cliente = accept(socket_servidor, &dir_cliente, &tam_direccion);
	if (socket_cliente > 0) {
		log_info(logger_servidor, "Se conecto un cliente!");
	}
	else {
		log_error(logger_servidor, "Ocurrió un error en el accept de esperar_cliente");
		log_error(logger_servidor, strerror(errno));
		return EXIT_FAILURE;
	}
	return socket_cliente;
}

e_proceso recibir_handshake(int socket_cliente) {
	e_operation_code op_code = recibir_operacion(socket_cliente);
	if (op_code == HANDSHAKE) {
		log_info(logger_servidor, "Handshake recibido");
		log_info(logger_servidor, "Ahora recibo el mensaje del handshake");
		char* buffer = recibir_mensaje(socket_cliente);
		e_proceso proceso = *buffer;
		free(buffer);
		switch(proceso) {
		case LFS:
			log_info(logger_servidor, "Se conecto un LFS");
			break;
		case MEMORIES:
			log_info(logger_servidor, "Se conecto una MEMORIES");
			break;
		case KERNEL:
			log_info(logger_servidor, "Se conecto un KERNEL");
			break;
		}
		return proceso;
	}
	else {
		log_error(logger_servidor, "La operación que llegó no es un handshake");
		return -1;
	}
}

int recibir_operacion(int socket_cliente) {
	e_operation_code cod_op;
	if (recv(socket_cliente, &cod_op, sizeof(e_operation_code), MSG_WAITALL) != 0) {
		return cod_op;
	}
	else {
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer(int* size, int socket_cliente) {
	void * buffer;
	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);
	return buffer;
}

char* recibir_mensaje(int socket_cliente) {
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger_servidor, "Me llego el mensaje %s", buffer);
	return buffer;
}

t_list* recibir_paquete(int socket_cliente) {
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;
	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size) {
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento += sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer + desplazamiento, tamanio);
		desplazamiento += tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}

void destruir_servidor() {
	log_destroy(logger_servidor);
}

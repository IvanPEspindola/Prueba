#include "lfs.h"

int main(void) {
	void imprimir(char* value) {
		printf("%s\n", value);
	}

	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor("127.0.0.1", "4444");
	log_info(logger, "Servidor listo para recibir al cliente");
	int cliente_fd = esperar_cliente(server_fd);
	e_proceso proceso = recibir_handshake(cliente_fd);
	t_list * lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			printf("Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) imprimir);
			break;
		case -1:
			log_error(logger, "El cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger, "Operacion desconocida.");
			break;
		}
	}
	return EXIT_SUCCESS;
}

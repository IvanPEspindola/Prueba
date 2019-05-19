#include "lfs.h"

void destruir_elemento(char* elemento);

int main(int argc, char** argv) {
	void imprimir(char* value) {
		printf("%s\n", value);
	}

	LOGGER_LFS = log_create("log-lfs.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	log_info(LOGGER_LFS, "Iniciando LFS.");

	if(leerConfiguracionLFS() == EXIT_SUCCESS){
		log_info(LOGGER_LFS, "Configuracion de LFS leído exitosamente.");
	}
	else {
		log_error(LOGGER_LFS ,"No se pudo levantar la configuracion del LFS. Abortando.");
		return EXIT_FAILURE;
	}

	loguear(INFO, string_from_format("Instancia iniciada [Puerto escucha: %d - Punto montaje: %s - Tamanio value: %d - Retardo: %d - Tiempo dump: %d]",
				configuracionLFS.PUERTO_ESCUCHA,
				configuracionLFS.PUNTO_MONTAJE,
				configuracionLFS.TAMANIO_VALUE,
				configuracionLFS.RETARDO,
				configuracionLFS.TIEMPO_DUMP)
				);

	int server_fd = iniciar_servidor("127.0.0.1", configuracionLFS.PUERTO_ESCUCHA);
	log_info(LOGGER_LFS, "Servidor listo para recibir al cliente");
	int cliente_fd = esperar_cliente(server_fd);

	e_proceso proceso = recibir_handshake(cliente_fd);
	t_list * lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case SELECT:
			lista = recibir_paquete(cliente_fd);
			printf("Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) imprimir);
			list_destroy_and_destroy_elements(lista, (void*) destruir_elemento);
			break;
		case -1:
			log_error(LOGGER_LFS, "El cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(LOGGER_LFS, "Operacion desconocida.");
			break;
		}
	}
	loguear(INFO, string_from_format("Destruyendo instancia"));
	destruir_servidor();
	log_destroy(LOGGER_LFS);
	return EXIT_SUCCESS;
}

void destruir_elemento(char* elemento) {
	free(elemento);
}

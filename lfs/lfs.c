#include "lfs.h"

int main(int argc, char** argv) {
	LOGGER_LFS = log_create("log-lfs.log", "LFS", 1, LOG_LEVEL_DEBUG);
	log_info(LOGGER_LFS, "Iniciando LFS");
	if (inicializarLFS() == EXIT_FAILURE) {
		loguear(ERROR, string_duplicate("Error al inicializar el LFS"));
		return EXIT_FAILURE;
	}
	int server_fd = iniciar_servidor("127.0.0.1", configuracionLFS.PUERTO_ESCUCHA);
	loguear(INFO, string_duplicate("Servidor listo para recibir clientes"));
	int cliente_fd;
	while(1) {
		loguear(INFO, string_duplicate("Esperando cliente..."));
		cliente_fd = esperar_cliente(server_fd);
		if (cliente_fd > 0) {
			pthread_create(&hiloMemorie, NULL, (void*) atenderMemorie, (void*) cliente_fd);
		}
	}
	loguear(INFO, string_duplicate("Destruyendo LFS"));
	destruir_servidor();
	log_destroy(LOGGER_LFS);
	return EXIT_SUCCESS;
}

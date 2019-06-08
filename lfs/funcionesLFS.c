#include "funcionesLFS.h"

#include <commons/string.h>

#include "lfs.h"


t_configuracionLFS configuracionLFS;
pthread_t hiloMemory;

int leerConfiguracionLFS() {
	bool cfgOk = true;
	loguear(INFO, string_from_format("Leyendo la configuracion del LFS : %s", LFS_DEFAULT_CONFIG_FILENAME));

	if (access(LFS_DEFAULT_CONFIG_FILENAME, F_OK ) != -1) {

		t_config * configuracion = config_create(LFS_DEFAULT_CONFIG_FILENAME);

		if (!config_has_property(configuracion, "PUERTO_ESCUCHA")) {
			log_error(LOGGER_LFS,ERR_LFS_LISTENING_PORT_NOT_SET);
			cfgOk = false;
		}

		if (!config_has_property(configuracion,"PUNTO_MONTAJE")) {
			log_error(LOGGER_LFS, ERR_LFS_MOUNT_POINT_NOT_SET);
			cfgOk = false;
		}

		if (!config_has_property(configuracion,"TAMANIO_VALUE")) {
			log_error(LOGGER_LFS, ERR_LFS_VALUE_SIZE);
			cfgOk = false;
		}

		if (!config_has_property(configuracion,"RETARDO")) {
			log_error(LOGGER_LFS,ERR_LFS_RET);
			cfgOk = false;
		}

		if (!config_has_property(configuracion,"TIEMPO_DUMP")) {
			log_error(LOGGER_LFS,ERR_LFS_DUMP_INTERVAL_NOT_SET);
			cfgOk = false;
		}

		if (cfgOk){
			configuracionLFS.PUERTO_ESCUCHA = string_duplicate(config_get_string_value(configuracion, "PUERTO_ESCUCHA"));
			configuracionLFS.PUNTO_MONTAJE 	= string_duplicate(config_get_string_value(configuracion, "PUNTO_MONTAJE"));
			configuracionLFS.TAMANIO_VALUE 	= config_get_int_value(configuracion, "TAMANIO_VALUE");
			configuracionLFS.RETARDO 		= config_get_int_value(configuracion, "RETARDO");
			configuracionLFS.TIEMPO_DUMP 	= config_get_int_value(configuracion, "TIEMPO_DUMP");

			config_destroy(configuracion);
		}else {
			config_destroy(configuracion);
			return EXIT_FAILURE;
		}

	}
	else {
		log_error(LOGGER_LFS, ERR_INST_CONFIG_FILE_NOT_FOUND);
		return EXIT_FAILURE;
        }

	return EXIT_SUCCESS;
}

int leerConfiguracionMetadata() {
	char * metadata_dir = string_duplicate(configuracionLFS.PUNTO_MONTAJE);
	string_append(&metadata_dir, "Metadata/");
	DIR * metadata_fd = opendir(metadata_dir);
	if (!metadata_fd) {
		loguear(ERROR, string_from_format("No se encontró el directorio de Metadata: %s", metadata_dir));
		free(metadata_dir);
		return EXIT_FAILURE;
	}
	else {
		closedir(metadata_fd);
		string_append(&metadata_dir, "Metadata.bin");
		if (access(metadata_dir, R_OK ) != -1) {
			t_config * configuracion_metadata = config_create(metadata_dir);
			bool cfgOk = true;
			if (!config_has_property(configuracion_metadata, "BLOCK_SIZE")) {
				log_error(LOGGER_LFS, ERR_LFS__METADATA_BLOCK_SIZE_NOT_SET);
				cfgOk = false;
			}
			if (!config_has_property(configuracion_metadata,"BLOCKS")) {
				log_error(LOGGER_LFS, ERR_LFS_METADATA_BLOCKS_NOT_SET);
				cfgOk = false;
			}
			if (!config_has_property(configuracion_metadata,"MAGIC_NUMBER")) {
				log_error(LOGGER_LFS, ERR_LFS_METADATA_MAGIC_NUMBER_NOT_SET);
				cfgOk = false;
			}
			if (cfgOk) {
				metadata_LFS.MAGIC_NUMBER = string_duplicate(config_get_string_value(configuracion_metadata, "MAGIC_NUMBER"));
				metadata_LFS.BLOCKS = config_get_int_value(configuracion_metadata, "BLOCKS");
				metadata_LFS.BLOCK_SIZE = config_get_int_value(configuracion_metadata, "BLOCK_SIZE");
			}
			config_destroy(configuracion_metadata);
		}
		free(metadata_dir);
	}
	return EXIT_SUCCESS;
}

void imprimir(char * value) {
	printf("%s\n", value);
}

void liberarMensajes(char * mensaje) {
	free(mensaje);
}

int createTable(char * table, char ** table_dir, int cliente_fd) {
	*table_dir = string_duplicate(tables_dir);
	string_to_upper(table);
	string_append(table_dir, table);
	string_append(table_dir, "/");
	DIR * table_fd = opendir(*table_dir);
	if (table_fd) {
		loguear(ERROR, string_from_format("CREATE ERROR: Table %s already exists", table));
		enviar_mensaje(ERROR_TABLE_ALREADY_EXISTS, "", cliente_fd);
		closedir(table_fd);
		return EXIT_FAILURE;
	}
	else {
		mkdir(*table_dir, S_IRWXU);
	}
	closedir(table_fd);
	return EXIT_SUCCESS;
}

char * createTableMetadata(char * table_dir, t_list * mensajes) {
	char* metadata_dir = string_duplicate(table_dir);
	string_append(&metadata_dir, "Metadata.bin");
	int metadata_fd = open(metadata_dir, O_RDWR | O_CREAT, S_IRWXU);
	close(metadata_fd);
	t_config* metadata = config_create(metadata_dir);
	char* consistency = string_duplicate(list_get(mensajes, 1));
	string_to_upper(consistency);
	config_set_value(metadata, "CONSISTENCY", consistency);
	free(consistency);
	char* partitions = string_duplicate(list_get(mensajes, 2));
	config_set_value(metadata, "PARTITIONS", partitions);
	char* compactation_time = string_duplicate(list_get(mensajes, 3));
	config_set_value(metadata, "COMPACTATION_TIME", compactation_time);
	free(compactation_time);
	config_save(metadata);
	config_destroy(metadata);
	free(metadata_dir);
	return partitions;
}

void createTablePartitions(char * partitions, char * table_dir) {
	int particiones = atoi(partitions);
	for (int i = 1; i <= particiones; i++) {
		char* partition_dir = string_duplicate(table_dir);
		char * partition_file = string_from_format("%d.bin", i);
		string_append(&partition_dir, partition_file);
		free(partition_file);
		int partition_fd = open(partition_dir, O_RDWR | O_CREAT, S_IRWXU);
		close(partition_fd);
		t_config* partition = config_create(partition_dir);
		char* size = string_itoa(0);
		config_set_value(partition, "SIZE", size);
		free(size);
		int block = obtenerProximoBloqueLibre();
		char* blocks = string_from_format("[%d]", block);
		config_set_value(partition, "BLOCKS", blocks);
		free(blocks);
		free(partition_dir);
		config_save(partition);
		config_destroy(partition);
	}
}

void create_operacion(int cliente_fd) {
	loguear(INFO, string_duplicate("Llegó un CREATE"));
	t_list * mensajes = recibir_paquete(cliente_fd);
	char * table_dir;
	char * table = string_duplicate(list_get(mensajes, 0));
	if (createTable(table, &table_dir, cliente_fd) == EXIT_FAILURE) {
		free(table);
		free(table_dir);
		list_destroy_and_destroy_elements(mensajes, (void *) liberarMensajes);
		return;
	}
	char * partitions = createTableMetadata(table_dir, mensajes);
	createTablePartitions(partitions, table_dir);
	free(partitions);
	free(table_dir);
	loguear(INFO, string_from_format("CREATE %s ejecutado correctamente", table));
	free(table);
	list_destroy_and_destroy_elements(mensajes, (void *) liberarMensajes);
	enviar_mensaje(SUCCESS, "", cliente_fd);
}

void insert_operacion(int cliente_fd) {
	loguear(INFO, string_duplicate("Llegó un INSERT"));
	t_list* mensajes = recibir_paquete(cliente_fd);
	printf("Me llegaron los siguientes mensajes\n");
	list_iterate(mensajes, (void*) imprimir);
	loguear(INFO, string_duplicate("Falta implementar"));
}

void select_operacion(int cliente_fd) {
	loguear(INFO, string_duplicate("Llegó un SELECT"));
	t_list* mensajes = recibir_paquete(cliente_fd);
	printf("Me llegaron los siguientes mensajes\n");
	list_iterate(mensajes, (void*) imprimir);
	loguear(INFO, string_duplicate("Falta implementar"));
}

void describe_operacion(int cliente_fd) {
	loguear(INFO, string_duplicate("Llegó un SELECT"));
	t_list* mensajes = recibir_paquete(cliente_fd);
	printf("Me llegaron los siguientes mensajes\n");
	list_iterate(mensajes, (void*) imprimir);
	loguear(INFO, string_duplicate("Falta implementar"));
}

void drop_operacion(int cliente_fd) {
	loguear(INFO, string_duplicate("Llegó un SELECT"));
	t_list* mensajes = recibir_paquete(cliente_fd);
	printf("Me llegaron los siguientes mensajes\n");
	list_iterate(mensajes, (void*) imprimir);
	loguear(INFO, string_duplicate("Falta implementar"));
}

void journal_operacion(int cliente_fd) {
	loguear(INFO, string_duplicate("Llegó un SELECT"));
	t_list* mensajes = recibir_paquete(cliente_fd);
	printf("Me llegaron los siguientes mensajes\n");
	list_iterate(mensajes, (void*) imprimir);
	loguear(INFO, string_duplicate("Falta implementar"));
}

void atenderMemory(int cliente_fd) {
	loguear(INFO, string_duplicate("Se creó el hilo para atender la petición"));
	int cod_op;
	cod_op = recibir_operacion(cliente_fd);
	switch (cod_op) {
	case SELECT:
		select_operacion(cliente_fd);
		break;
	case INSERT:
		insert_operacion(cliente_fd);
		break;
	case CREATE:
		create_operacion(cliente_fd);
		break;
	case DESCRIBE:
		describe_operacion(cliente_fd);
		break;
	case DROP:
		drop_operacion(cliente_fd);
		break;
	case JOURNAL:
		journal_operacion(cliente_fd);
		break;
	default:
		loguear(ERROR, string_duplicate("Operacion desconocida"));
		break;
	}
}

void inicializarDirectorioTablas() {
	tables_dir = string_duplicate(configuracionLFS.PUNTO_MONTAJE);
	string_append(&tables_dir, "Tables/");
	DIR* tables_fd = opendir(tables_dir);
	if (!tables_fd) {
		mkdir(tables_dir, S_IRWXU);
	}
	closedir(tables_fd);
}

int inicializarLFS() {
	loguear(INFO, string_duplicate("Incializando cuestiones administrativas"));
	if (leerConfiguracionLFS() == EXIT_SUCCESS){
		loguear(INFO, string_duplicate("Configuracion de LFS leído exitosamente."));
	}
	else {
		loguear(INFO, string_duplicate("No se pudo levantar la configuracion del LFS. Abortando."));
		return EXIT_FAILURE;
	}
	loguear(INFO, string_from_format("Instancia iniciada [Puerto escucha: %s - Punto montaje: %s - Tamanio value: %d - Retardo: %d - Tiempo dump: %d]",
				configuracionLFS.PUERTO_ESCUCHA,
				configuracionLFS.PUNTO_MONTAJE,
				configuracionLFS.TAMANIO_VALUE,
				configuracionLFS.RETARDO,
				configuracionLFS.TIEMPO_DUMP)
				);
	DIR * lfs_fd = opendir(configuracionLFS.PUNTO_MONTAJE);
	if (!lfs_fd) {
		closedir(lfs_fd);
		loguear(ERROR, string_from_format("El punto de montaje %s es inválido", configuracionLFS.PUNTO_MONTAJE));
		return EXIT_FAILURE;
	}
	else {
		inicializarDirectorioTablas();;
		return leerConfiguracionMetadata();
	}
}

int obtenerProximoBloqueLibre() {
	// TODO LFS: FALTA IMPLEMENTAR EL BITMAP DE BLOQUES Y DEVOLVER EL PROXIMO BLOQUE LIBRE. POR AHORA SE HARDCODEA PARA DEVOVLER 1
	return 1;
}



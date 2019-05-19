#include "funcionesLFS.h"
#include "lfs.h"

t_configuracionLFS configuracionLFS;

int leerConfiguracionLFS() {
	bool cfgOk = true;
	loguear(INFO, string_from_format("Leyendo la configuracion del LFS : %s", LFS_DEFAULT_CONFIG_FILENAME));

	if( access(LFS_DEFAULT_CONFIG_FILENAME, F_OK ) != -1 ) {

		t_config * configuracion = config_create(LFS_DEFAULT_CONFIG_FILENAME);

		if(!config_has_property(configuracion, "PUERTO_ESCUCHA")) {
			log_error(LOGGER_LFS,ERR_LFS_LISTENING_PORT_NOT_SET);
			cfgOk = false;
		}

		if(!config_has_property(configuracion,"PUNTO_MONTAJE")) {
			log_error(LOGGER_LFS, ERR_LFS_MOUNT_POINT_NOT_SET);
			cfgOk = false;
		}

		if(!config_has_property(configuracion,"TAMANIO_VALUE")) {
			log_error(LOGGER_LFS, ERR_LFS_VALUE_SIZE);
			cfgOk = false;
		}

		if(!config_has_property(configuracion,"RETARDO")) {
			log_error(LOGGER_LFS,ERR_LFS_RET);
			cfgOk = false;
		}

		if(!config_has_property(configuracion,"TIEMPO_DUMP")) {
			log_error(LOGGER_LFS,ERR_LFS_DUMP_INTERVAL_NOT_SET);
			cfgOk = false;
		}

		if(cfgOk){
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
		log_error(LOGGER_LFS,ERR_INST_CONFIG_FILE_NOT_FOUND);
		return EXIT_FAILURE;
        }

	return EXIT_SUCCESS;
}

#include "kernel.h"

int main(void) {

	inicializar();

	log_info(logger, "Iniciando API.");
	ejecutar_consola();

	log_info(logger, "Finalizando Kernel.");
	finalizar();

	return EXIT_SUCCESS;
}

void inicializar(){

	logger = log_create("kernel.log", "kernel", 1, LOG_LEVEL_INFO);
	log_info(logger, "Iniciando Kernel...");

	config = generar_config();
	cargar_config(config);
	log_info(logger,"Se cargo correctamente el archivo de configuracion.");

	if((socketMemoria = crear_conexion_cliente(configData.ip_memoria, configData.puerto_memoria)) == -1){
		log_error(logger, "Error al crear conexion con Memoria.");
		finalizar();
	}
	log_info(logger,"Se ha conectado con MEMORIA. IP: %s - PUERTO: %d ",configData.ip_memoria,configData.puerto_memoria);

	//Cargar metadata de pool de memorias

	log_info(logger, "Inicializacion completa.");
}

t_config* generar_config(){
	t_config* configuracion;
	if((configuracion = config_create(CONFIG_PATH)) == NULL){
		log_error(logger, "Error al crear el t_config.");
		exit(-1);
	}
	return configuracion;
}

void cargar_config(){

    if(!config_has_property(config, "IP_MEMORIA")){
        log_error(logger, "No se encuentra IP_MEMORIA en el archivo de configuracion.");
        log_destroy(logger);
        exit(-1);
    }else{
    	configData.ip_memoria = string_new();
    	string_append(&configData.ip_memoria, config_get_string_value(config, "IP_MEMORIA"));
    }
    if(!config_has_property(config, "PUERTO_MEMORIA")){
        log_error(logger, "No se encuentra PUERTO_MEMORIA en el archivo de configuracion.");
        log_destroy(logger);
        exit(-1);
    }else{
    	configData.puerto_memoria = string_new();
    	string_append(&configData.puerto_memoria, config_get_string_value(config, "PUERTO_MEMORIA"));
    }
    if(!config_has_property(config, "QUANTUM")){
		log_error(logger, "No se encuentra QUANTUM en el archivo de configuracion.");
		log_destroy(logger);
		exit(-1);
	}else{
		configData.quantum = config_get_int_value(config, "QUANTUM");
	}
    if(!config_has_property(config, "MULTIPROCESAMIENTO")){
		log_error(logger, "No se encuentra MULTIPROCESAMIENTO en el archivo de configuracion.");
		log_destroy(logger);
		exit(-1);
	}else{
		configData.multiprocesamiento = config_get_int_value(config, "MULTIPROCESAMIENTO");
	}
    if(!config_has_property(config, "METADATA_REFRESH")){
		log_error(logger, "No se encuentra METADATA_REFRESH en el archivo de configuracion.");
		log_destroy(logger);
		exit(-1);
	}else{
		configData.metadata_refresh = config_get_int_value(config, "METADATA_REFRESH");
	}
    if(!config_has_property(config, "SLEEP_EJECUCION")){
		log_error(logger, "No se encuentra SLEEP_EJECUCION en el archivo de configuracion.");
		log_destroy(logger);
		exit(-1);
	}else{
		configData.sleep_ejecucion = config_get_int_value(config, "SLEEP_EJECUCION");
	}
    config_destroy(config);
}

void finalizar(){
	shutdown(socketMemoria,2);
	log_destroy(logger);
}

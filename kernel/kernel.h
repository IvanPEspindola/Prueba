#ifndef KERNEL_H_
#define KERNEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sockets/sockets_cliente.h>

#include "kernel_shared.h"

#define CONFIG_PATH "./kernel.ini"

typedef struct {
	char * ip_memoria;
	char * puerto_memoria;
	int quantum;
	int multiprocesamiento;
	int metadata_refresh;
	int sleep_ejecucion;
} t_configData;

t_config* config;
t_configData configData;
int socketMemoria;

void inicializar();
t_config* generar_config();
int existe_archivo(char * path);
void cargar_config();
void finalizar();

#endif /* KERNEL_H_ */

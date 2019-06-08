#ifndef MEMORIES_H_
#define MEMORIES_H_

#include <sockets/sockets_cliente.h>
#include <sockets/sockets_servidor.h>
#include "sockets/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>

typedef struct config
{
	int id_memory;
	char* ip_MEM;
	char* port_MEM;
	char* port_FS;
	char* ip_FS;
	char** ip_seeds;
	char** port_seeds;
	int retardo_MEM;
	int retardo_FS;
	int tam_mem;
	int retardo_jurnal;
	int retardo_gossiping;

} config;

t_log * pLog;

typedef	struct nodop{
	int NumPagina;
	int DirMemoria;
	int flagMod;
	struct nodop *siguiente;
	struct nodop *anterior;
}Pagina;

typedef	struct nodos{
	int NumSegmento;
	Pagina *pagina;
	struct nodos *siguiente;
	struct nodos *anterior;
}Segmento;


#endif /* MEMORIES_H_ */

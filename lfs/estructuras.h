#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct ConfiguracionLFS {
	char * PUERTO_ESCUCHA;
	char * PUNTO_MONTAJE;
	int TAMANIO_VALUE;
	int RETARDO;
	int TIEMPO_DUMP;
} t_configuracionLFS;

typedef enum {
	INFO,
	ERROR
} TIPO_ERROR;

#endif

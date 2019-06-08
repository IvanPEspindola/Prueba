#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct ConfiguracionLFS {
	char * PUERTO_ESCUCHA;
	char * PUNTO_MONTAJE;
	int TAMANIO_VALUE;
	int RETARDO;
	int TIEMPO_DUMP;
} t_configuracionLFS;

typedef struct Metadata_LFS {
	int BLOCK_SIZE;
	int BLOCKS;
	char * MAGIC_NUMBER;
} t_metadataLFS;

typedef enum {
	INFO,
	ERROR
} TIPO_ERROR;

#endif

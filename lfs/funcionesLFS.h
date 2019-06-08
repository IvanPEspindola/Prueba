#ifndef FUNCIONES_LFS_H_
#define FUNCIONES_LFS_H_

#include "auxiliares.h"

int leerConfiguracionLFS();
int leerConfiguracionMetadata();
void imprimir(char * value);
void liberarMensajes(char * mensaje);
int createTable(char * table, char ** table_dir, int cliente_fd);
char * createTableMetadata(char * table_dir, t_list * mensajes);
void createTablePartitions(char * partitions, char * table_dir);
void create_operacion(int cliente_fd);
void insert_operacion(int cliente_fd);
void select_operacion(int cliente_fd);
void describe_operacion(int cliente_fd);
void drop_operacion(int cliente_fd);
void journal_operacion(int cliente_fd);
void atenderMemory(int cliente_fd);
void inicializarDirectorioTablas();
int inicializarLFS();
int obtenerPrimerBloqueLibreYOcuparlo();
void crearBitmapBloques();

#endif /* FUNCIONES_LFS_H_ */

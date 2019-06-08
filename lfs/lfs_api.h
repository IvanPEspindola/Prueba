#ifndef LFS_API_H_
#define LFS_API_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lfs_parser.h"

typedef struct {
	int code;
	char* name; // Nombre del comando
} COMMAND;

COMMAND commands[] = {
	{ 1,"SELECT"},
	{ 2,"INSERT"},
	{ 3,"CREATE"},
	{ 4,"DESCRIBE"},
	{ 5,"DROP"},
	{ 6,"SALIR"}
};

int cantCommands = 6;

int salir = 0;

void ejecutar_consola();
void analizar_linea(char* string);
void help();

#endif /* KERNEL_API_H_ */

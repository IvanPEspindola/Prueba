#ifndef KERNEL_API_H_
#define KERNEL_API_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "kernel_parser.h"

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
	{ 6,"JOURNAL"},
	{ 7,"ADD"},
	{ 8,"RUN"},
	{ 9,"METRICS"},
	{ 10,"HELP"},
	{ 11, "SALIR"}
};

int cantCommands = 11;

int salir = 0;

void ejecutar_consola();
void analizar_linea(char* string);
void help();

#endif /* KERNEL_API_H_ */

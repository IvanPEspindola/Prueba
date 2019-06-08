#ifndef KERNEL_PARSER_H_
#define KERNEL_PARSER_H_

#include "kernel_shared.h"


void new_request(int codigo, char** array);
int parametros_ok(char** array, int codigo);
void journal();
void metrics();
void add(char* numero, char* criterio);
void run(char* path);

#endif /* KERNEL_PARSER_H_ */

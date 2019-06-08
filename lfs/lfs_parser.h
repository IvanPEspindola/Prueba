#ifndef LFS_PARSER_H_
#define LFS_PARSER_H_

#include <string.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <commons/string.h>
#include <commons/config.h>

t_log *logger;


void new_request(int codigo, char** array);
int parametros_ok(char** array, int codigo);
void add(char* numero, char* criterio);
void run(char* path);

#endif /* LFS_PARSER_H_ */

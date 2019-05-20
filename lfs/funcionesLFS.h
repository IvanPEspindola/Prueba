#ifndef FUNCIONES_INSTANCIA_H_
#define FUNCIONES_INSTANCIA_H_

#include "funcionesLFS.h"
#include "auxiliares.h"
#include "estructuras.h"
#include <string.h>

int leerConfiguracionLFS(char* filePath);

extern t_log *  LOG_LFS;
extern t_configuracionLFS configuracionLFS;

#endif /* FUNCIONES_INSTANCIA_H_ */

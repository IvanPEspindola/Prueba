#ifndef MEMORYADMIN_H_
#define MEMORYADMIN_H_

#include <sockets/sockets_cliente.h>
#include "sockets/utils.h"
#include "memories.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>

void setearConfiguracion(config* configMem);
void handshakeLFS(int* socket);
void handshakeKernel(int* socket);
void handshakeOtherMemory(int* socket);
void gossiping(int* socket);//devuelvo mis tablas a quien me pidio
void comenzarGossiping(config* configMem);//jodo a mis seeds para actualizar



t_list memorypool;

#endif /* MEMORYADMIN_H_ */

#ifndef AUXILIARES_H_
#define AUXILIARES_H_

#include "estructuras.h"
#include "errors.h"
#include <stdlib.h>
#include <commons/log.h>
#include "estructuras.h"
#include <commons/string.h>
#include <errno.h>
#include <dirent.h>
#include <sockets/utils.h>
#include <commons/collections/list.h>
#include <stdio.h>
#include <unistd.h>
#include <commons/config.h>
#include <sockets/sockets_servidor.h>
#include <sockets/sockets_cliente.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LFS_DEFAULT_CONFIG_FILENAME "lfs.cfg"
t_log * LOGGER_LFS;
t_configuracionLFS configuracionLFS;
pthread_t hiloMemorie;
char * tables_dir;
t_metadataLFS metadata_LFS;

void loguear(TIPO_ERROR te, char * mensaje);

#endif /* AUXILIARES_H_ */

#ifndef AUXILIARES_H_
#define AUXILIARES_H_

#include "lfs.h"
#include "estructuras.h"
#include "errors.h"
#include <commons/log.h>
#include <commons/config.h>

#define LFS_DEFAULT_CONFIG_FILENAME "lfs.cfg"

void loguear(TIPO_ERROR te, char * mensaje);

#endif /* AUXILIARES_H_ */

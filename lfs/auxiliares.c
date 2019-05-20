#include "auxiliares.h"

void loguear(TIPO_ERROR te, char * mensaje)
{
	switch(te) {
		case INFO:
			log_info(LOGGER_LFS, mensaje);
			break;
		case ERROR:
			log_error(LOGGER_LFS, mensaje);
			break;
	}

	free(mensaje);
}

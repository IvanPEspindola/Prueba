#include "lfs_parser.h"

void new_request(int codigo, char** array){

	switch(codigo){
		case 1: //SELECT
			// TODO: Definir si lo mandamos por sockets o llamamos directamente al a func SELECT_OPERACION
			break;
		case 2: //INSERT

			break;
		case 3: //CREATE

			break;
		case 4: //DESCRIBE

			break;
		case 5: //DROP

			break;
		default:
			break;
	}
};

int parametros_ok(char** array, int codigo){

	switch(codigo){
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 7:
			break;
		case 8:
			break;
		default:
			break;
	}

	return 0;
}

void add(char* numero, char* criterio){}
void run(char* path){}


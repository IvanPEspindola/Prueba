#include "kernel_parser.h"

void new_request(int codigo, char** array){

	switch(codigo){
		case 1: //SELECT

			break;
		case 2: //INSERT

			break;
		case 3: //CREATE

			break;
		case 4: //DESCRIBE

			break;
		case 5: //DROP

			break;
		case 6: //JOURNAL
			journal();
			break;
		case 7: //ADD
			if(parametros_ok(array, codigo)) add(array[2], array[4]);
			break;
		case 8: //RUN
			if(parametros_ok(array, codigo)) run(array[1]);
			break;
		case 9: //METRICS
			metrics();
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

void journal(){}
void metrics(){}
void add(char* numero, char* criterio){}
void run(char* path){}


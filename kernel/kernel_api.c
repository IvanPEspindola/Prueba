#include "kernel_api.h"

void ejecutar_consola(){

	puts("");
	puts("-----------------------------------------------");
	puts("[KERNEL API] - Lissandra 2019 \"404-Not-found\"");
	puts("-----------------------------------------------");
	puts("");

	char* linea;
	salir = 0;

	while (salir == 0) {

		linea = readline("-> ");
		if (!linea)	break;

		analizar_linea(linea);

		free(linea);
	}
}

void analizar_linea(char* string){

	int codigo = 0;

	char** splitString = string_split(string, " ");
	char* comando = splitString[0];

	int i;
	for(i = 0; i < cantCommands; i++){
		if(strcasecmp(comando, commands[i].name) == 0){
			codigo = commands[i].code;
			break;
		}
	}

	switch(codigo){
		case 0:
			log_error(logger, "Comando no reconocido. Escriba 'help' para obtener una lista de comandos.");
			return;
		case 10:
			help();
			return;
		case 11:
			salir = 1;
			return;
		default:
			new_request(codigo, splitString);
	}

}

void help(){
	puts("");
	puts("# Comandos Disponibles: ");
	puts("");
	puts("- SELECT [NOMBRE_TABLA] [KEY]");
	puts("- INSERT [NOMBRE_TABLA] [KEY] “[VALUE]”");
	puts("- CREATE [TABLA] [TIPO_CONSISTENCIA] [NUMERO_PARTICIONES] [COMPACTION_TIME]");
	puts("- DESCRIBE [NOMBRE_TABLA]");
	puts("- DROP [NOMBRE_TABLA]");
	puts("- JOURNAL");
	puts("- ADD MEMORY [NÚMERO] TO [CRITERIO]");
	puts("- RUN [PATH_TO_SCRIPT]");
	puts("- METRICS");
	puts("- SALIR");
	puts("");
}

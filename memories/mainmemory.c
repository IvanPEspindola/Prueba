#include "memories.h"

char* memoria;
int tamanioKeyYTimestamp=26;
int tamanioValue;

char* setearMainMemory(int tamanioMem)
{
	//memoria= malloc(tamanioMem);
	//tamanioValue=tamanioMem;

	//por ahora hardcodeado
	memoria=(char*)malloc(40);

	tamanioValue=14;
	return memoria;
}

void insertarEnArray(int direccion, char* value)
{
	char* memoria=setearMainMemory(40);
	int i=0;
	int valueSize=sizeof(value);
	//LLeno con el valor
	while(i<valueSize)
	{
		memoria[direccion+tamanioKeyYTimestamp+i]=	value[i];
		printf("%s\n",memoria);
		i=i+1;
	}

//null el resto de los valores
	if (valueSize<tamanioValue)
	{
		while(valueSize+1!=tamanioValue)
		{
			memoria[direccion+tamanioKeyYTimestamp+valueSize+1]=NULL;
			valueSize++;
		}
	}
	/*int p=0;
	while(p<=40){
		printf("%s\n",memoria[p]);
		p++;
	}*/

}


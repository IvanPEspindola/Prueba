#include "memories.h"

/*int ContadorDeDireccion=0;
int TamañoMarco=40;*/
Segmento *tablaDeSegmentos(Segmento *TablaSeg){ //CREA TABLA DE SEGMENTOS

	TablaSeg = NULL;
	return TablaSeg;
}

Pagina *tablaDePaginas(Pagina *TablaPag){ //CREA TABLA DE PAGINAS

	TablaPag = NULL;
	return TablaPag;
}

Segmento *agregarSegmentos(Segmento *TablaSeg, int NumSegmento/*, int TamSegmento*/) //AGREGA UN SEGMENTO A LA TABLA DE SEGMENTOS
{
	Segmento *nuevoSegmento,*aux;
	Pagina *TablaPag = tablaDePaginas(TablaPag); //crea una tabla de pag
	nuevoSegmento=malloc(sizeof(Segmento));
	nuevoSegmento->NumSegmento = NumSegmento;
	nuevoSegmento->pagina = TablaPag;
	nuevoSegmento->siguiente = NULL;

	if(TablaSeg == NULL){
		TablaSeg = nuevoSegmento;
	}else{
		aux = TablaSeg;
		while(aux->siguiente != NULL){
			aux = aux->siguiente;
		}
		aux->siguiente = nuevoSegmento;
		aux->siguiente->anterior=aux;
	}

	/*int contador=0;
	while(contador<=TamSegmento){
		agregarPaginas(TablaSeg,NULL,ContadorDeDireccion,NULL,NumSegmento);
		ContadorDeDireccion=ContadorDeDireccion+TamañoMarco;
	}*/

	return TablaSeg;
}

Segmento *buscarSegmento(Segmento *TablaSeg, int NumSegmento) //BUSCA UN SEGMENTO EN LA TABLA DE SEGMENTOS
{
	Segmento *buscador;
	if(TablaSeg == NULL)
	{
		printf("%s\n","La tabla no contiene segmentos");
	}else
	{
		buscador = TablaSeg;
		while(buscador != NULL)
		{
			if(buscador->NumSegmento == NumSegmento)
			{
				return buscador;
			}else
			{
				buscador=buscador->siguiente;
			}
		}
		printf("%s\n","No existe el segmento solicitado");
	}
	return 0;
}



void agregarPaginas(Segmento *TablaSeg, int NumPagina, int DirMemoria, int flagMod, int NumSeg ) //AGREGA UNA PAGINA A LA TABLA DE PAGINAS
{
	Pagina *nuevaPagina,*aux;
	nuevaPagina=malloc(sizeof(Pagina));
	nuevaPagina->NumPagina = NumPagina;
	nuevaPagina->DirMemoria = DirMemoria;
	nuevaPagina->flagMod = flagMod ;
	nuevaPagina->siguiente = NULL;

	Segmento* segmento = buscarSegmento(TablaSeg,NumSeg);

	if(segmento->pagina == NULL){
		segmento->pagina = nuevaPagina;
	}else{
		aux = segmento->pagina;
		while(aux->siguiente != NULL){
			aux = aux->siguiente;
		}
		aux->siguiente = nuevaPagina;
		aux->siguiente->anterior=aux;
	}
}

Pagina *buscarPagina(Pagina *TablaPag, int NumPagina) //BUSCA UNA PAGINA EN LA TABLA DE PAGINAS
{
	Pagina *buscador;
	if(TablaPag == NULL)
	{
		printf("%s\n","La tabla no contiene paginas");
	}else
	{

		buscador = TablaPag;
		while(buscador != NULL)
		{
			if(buscador->NumPagina == NumPagina)
			{
				return buscador;
			}else
			{
				buscador=buscador->siguiente;
			}
		}
		printf("%s\n","No existe la pagina solicitada");
	}
	return 0;
}

Pagina *buscar(Segmento *TablaSeg, int NumSegmento, int NumPagina) //BUSCA UNA PAGINA EN EL SISTEMA COMPLETO
{
	Segmento *segmento = buscarSegmento(TablaSeg,NumSegmento);
	Pagina *TabPagina = segmento->pagina;
	Pagina *pagina = buscarPagina(TabPagina,NumPagina);
	return pagina;
}

void eliminarPagina(Segmento *TablaSeg, int NumSegmento, int NumPagina) //ELIMINA UNA PAGINA
{
	Pagina *pagina=buscar(TablaSeg,NumSegmento,NumPagina);
	Pagina *aux=pagina->anterior;
	pagina->anterior->siguiente=pagina->siguiente;
	pagina->siguiente->anterior=aux;
	pagina=NULL;
}


int chequearFlagMod(Pagina *pagina){
	if (pagina->flagMod==0){
		return 0;
	}else if(pagina->flagMod==1){
		return 1;
	}else {
		printf("%s\n","ERROR: EL FLAG ES DESCONOCIDO");
		return 2;
	}
}

void insertarDatosEnPagina (Segmento *TablaSeg, int NumSegmento, int NumPagina,int NuevoNumPagina, int DirMemoria, int flagMod ) //Insterta datos en una pagina
{
	Pagina *pagina = buscar(TablaSeg,NumSegmento,NumPagina);
	pagina->NumPagina = NuevoNumPagina;
	pagina->DirMemoria = DirMemoria;
	pagina->flagMod = flagMod ;
}

Pagina* buscarPaginaVacia (Pagina *TablaPag)
{
	while(TablaPag != NULL)
	{
		if(TablaPag->NumPagina != NULL)
		{
			TablaPag = TablaPag->siguiente;
		}else {

			return TablaPag;
		}
	}
	return 0;
}

void insert (Segmento* TablaSeg, int NumSeg, int NumPag,char* Value){

	Segmento * segmento = buscarSegmento(TablaSeg,NumSeg);
	if(segmento!=0)//si encontró el segmento
	{
		printf("%s\n","encontre el segmento");
		Pagina *pagina = buscarPagina(segmento->pagina,NumPag);
		if(pagina!=0)//si encontró la pagina
		{
			printf("%s\n","encontre la pagina");
			int Direccion = pagina->DirMemoria;
			//inserto los datos en la direccion de memoria
			//insertarEnArray(Direccion,Value);
			pagina->flagMod=1;
		}
		else //si no encontro la pagina
		{
			Pagina *PaginaVacia = buscarPaginaVacia(segmento->pagina);
			if(PaginaVacia!=0)//si encontro una pagina vacía
			{
				int Direccion = PaginaVacia->DirMemoria;
				insertarDatosEnPagina(TablaSeg,NumSeg,PaginaVacia->NumPagina,NumPag,Direccion,1);
				//inserto los datos en la direccion de memoria
				//insetarEnArray(Direccion,Value);
			}
			else //si no hay una pagina vacía
			{
				//aplicar algoritmo de reemplazo o pedir journaling al kernel
			}
		}
	}
	else //si no encontró el segmento
	{
		Segmento *segNuevo = agregarSegmentos(TablaSeg,NumSeg); //agrega un segmento a la tabla de segmentos
		agregarPaginas(TablaSeg,NumPag,3,1,NumSeg); //agrega una pagina a la tabla de paginas del nuevo segmento
		//inserto los datos en la direccion de memoria de la nueva pagina
	}

}

char* selectt (Segmento* TablaSeg, int NumSeg, int NumPag){

	Pagina *paginasolicitada = buscar(TablaSeg,NumSeg,NumPag);
	char*a="a";
	if(paginasolicitada != NULL){ //si existe la pagina

		//busco en el array la direccion de la pag solicitada
		//char* value = buscarEnMemoria(paginasolicitada->direccion);
		//return value;

		return a;

	}else
	{
		//envío solicitud al filesystem;
		//selectLFS
		//insert()
		return a;
	}

}


int main(void) {

	/*LOGGER_M = log_create("log-m.log", "Memories", 1, LOG_LEVEL_DEBUG);
		log_info(LOGGER_M, "Hola");*/
	Segmento *TablaSeg = tablaDeSegmentos(TablaSeg);//crea una tabla de segmentos

		TablaSeg = agregarSegmentos(TablaSeg,1);
		TablaSeg = agregarSegmentos(TablaSeg,2);//agrega un segmento a la tabla


		agregarPaginas(TablaSeg,1,0,0,1);//agrega una pagina a la tabla
		/*agregarPaginas(TablaSeg,0,0,0,1);
		agregarPaginas(TablaSeg,0,0,0,1);*/
		/*agregarPaginas(TablaSeg,1,789,1,2);
		agregarPaginas(TablaSeg,2,910,1,2);*/

		insert(TablaSeg,1,1,"hola");
		//eliminarPagina(TablaSeg,1,2); //elimina una pagina;



	/*Pagina *paginadeseada = buscar(TablaSeg,1,1); //busca la pagina con el num de segmento y num de pag
	printf("%i\n",paginadeseada->NumPagina);
	printf("%i\n",paginadeseada->DirMemoria);
	printf("%i\n",paginadeseada->flagMod);*/



	/*while(TablaSeg != NULL){
		while(TablaSeg->pagina != NULL){
			printf("%i\n",TablaSeg->NumSegmento);
			printf("%i\n",TablaSeg->pagina->NumPagina);
			printf("%i\n",TablaSeg->pagina->DirMemoria);
			printf("%i\n",TablaSeg->pagina->flagMod);
			TablaSeg->pagina=TablaSeg->pagina->siguiente;
		}
		TablaSeg=TablaSeg->siguiente;
	}*/ //Recorre y muesta la lista completa

}

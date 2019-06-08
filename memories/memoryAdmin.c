#include "memoryAdmin.h"
#include "memories.h"


void setearConfiguracion(config* configMem)
{

	t_config * pConf = config_create("Memory.config");
	configMem->id_memory = config_get_int_value(pConf, "MEMORY_NUMBER");
	configMem->ip_MEM=config_get_string_value(pConf, "IP");
	configMem->port_MEM=config_get_string_value(pConf, "PUERTO");
	configMem->ip_FS=config_get_string_value(pConf,"IP_FS");
	configMem->port_FS=config_get_string_value(pConf, "PUERTO_FS");
	configMem->ip_seeds=config_get_array_value(pConf,"IP_SEEDS");
	configMem->port_seeds=config_get_array_value(pConf,"PUERTO_SEEDS");
	configMem->retardo_MEM=config_get_int_value(pConf, "RETARDO_MEM");
	configMem->retardo_FS=config_get_int_value(pConf, "RETARDO_FS");
	configMem->tam_mem=config_get_int_value(pConf, "TAM_MEM");
	configMem->retardo_jurnal=config_get_int_value(pConf, "RETARDO_JOURNAL");
	configMem->retardo_gossiping=config_get_int_value(pConf, "RETARDO_GOSSIPING");

	log_trace(pLog, "Configuracion Seteada");
	log_trace(pLog, "ID  de la memoria: %d", configMem->id_memory);

}

void handshakeLFS(int* socket)
{
	enviar_handshake(socket, MEMORIES);
	log_trace(pLog, "Handshake done");
}

void gossiping(int* socket)
{
	t_paquete* paquete = crear_paquete(GOSSIPING);


	agregar_a_paquete(paquete, &memorypool, sizeof(memorypool));
	enviar_paquete(paquete, *socket);
	eliminar_paquete(paquete);

}


/*bool igualarValores(gossipingData* data1,gossipingData* data2){
	if(data1==data2)
	return true;
	else
	return false;
}

bool compararlista(t_list* data2)
{
	 if(!list_any_satisfy(data, (void*)compararlista)
	 {

	 }
}

 void agregarAPool(t_list* data)
 {
	 if(!list_any_satisfy(data, (void*)igualarValores)
	 {

	 }
 }*/

void comenzarGossiping(config* configMem)
{
	//1. Jodo a mis seeds y les pido sus tablas
	t_list * lista;
	int i=0;
	while(configMem->port_seeds[i]!= NULL )
	{
		log_info(pLog, "Seed numero: %s. Pidiendo datos" , configMem->port_seeds[i]);

		int memoriesocket = crear_conexion_cliente(configMem->ip_seeds[i], configMem->port_seeds[i]);
		enviar_handshake(memoriesocket, MEMORIES);
		t_paquete* paquete = crear_paquete(GOSSIPING);
		lista=recibir_paquete(socket);
		//list_iterate(lista, (void*) agregarAPool);
		// liberar_conexion(int socket_cliente);//Una vez q tenga sus datos
		i++;
	}

	//recibir respuesta. Recibir las tablas.
	//2. Actualizo mis tablas
	//cada paquete q reciba es una linea

}

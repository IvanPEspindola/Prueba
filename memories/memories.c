#include "memories.h"
#include "memoryAdmin.h"
#include "sockets/utils.h"

void conectarseAlFileSystem();

	int socketLFS, cliente_Kernel;
	config configMem;

	void conectarseAlKernel();
	void conectarseAlFileSystem();


int main(void) {

	pLog = log_create("Memory.log", "Memory", true, LOG_LEVEL_TRACE);
	setearConfiguracion(&configMem);
	comenzarGossiping(&configMem);
	//conectarseAlFileSystem();
	//int valorDeValue=10;pedirle valor de value
	//setear tablas
	//hacer vector de memoriaMain

//	conectarseAlKernel();

	//inicializar tablas

	while (1) {

		int cod_op = recibir_operacion(cliente_Kernel);
		t_paquete* paquete;
			switch (cod_op) {
			case SELECT:
				break;
			case INSERT:

							break;
			case CREATE:

							break;
			case DESCRIBE:

							break;
			case DROP:

							break;
			case JOURNAL:

							break;
			case GOSSIPING:

				gossiping(&cliente_Kernel);
				break;
			case -1:
				log_error(pLog, "El cliente se desconecto. Terminando servidor");

				return EXIT_FAILURE;
			default:
				log_warning(pLog, "Operacion desconocida.");
				break;
			}

			//if succes
			//enviar_paquete(paquete, cliente_Kernel);
		}

	//rest...
		destruir_servidor();
//destruir config
		//liberar tablas

		return 0;
}

void conectarseAlFileSystem()
{
  socketLFS = crear_conexion_cliente(configMem.ip_FS, configMem.port_FS);
  handshakeLFS(&socketLFS);
}


void conectarseAlKernel()
{
	int socketKernel = iniciar_servidor(configMem.ip_MEM,configMem.port_MEM);
	log_info(pLog, "Servidor listo para recibir al cliente");
	int cliente_Kernel = esperar_cliente(socketKernel);
	/*e_proceso proceso =*/ recibir_handshake(cliente_Kernel);
}





















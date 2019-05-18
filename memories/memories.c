#include "memories.h"

int main(void) {
	int socket = crear_conexion_cliente("127.0.0.1", "4444");
	enviar_handshake(socket, MEMORIES);
	t_paquete* paquete = crear_paquete();
	agregar_a_paquete(paquete, "hola", 5);
	agregar_a_paquete(paquete, "pepe", 5);
	agregar_a_paquete(paquete, "!", 2);
	enviar_paquete(paquete, socket);
	eliminar_paquete(paquete);
//	enviar_mensaje();
}

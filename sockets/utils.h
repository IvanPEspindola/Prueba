#ifndef UTILS_H_
#define UTILS_H_

typedef enum {
	HANDSHAKE,
	PAQUETE
} e_operation_code;

typedef enum {
	KERNEL,
	MEMORIES,
	LFS
} e_proceso;

typedef struct
{
	int size;
	void* stream;
} t_buffer;


#endif /* UTILS_H_ */

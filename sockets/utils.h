#ifndef UTILS_H_
#define UTILS_H_

typedef enum {
	HANDSHAKE,
	SELECT,
	INSERT,
	CREATE,
	DESCRIBE,
	DROP,
	JOURNAL,
	GOSSIPING
} e_operation_code;

typedef enum {
	KERNEL,
	MEMORIES,
	LFS
} e_proceso;

typedef struct {
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	int id;
	char* ip;
	char* puerto;
}gossipingData;

#endif /* UTILS_H_ */

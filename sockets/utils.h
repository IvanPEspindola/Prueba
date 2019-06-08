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
	SUCCESS,
	ERROR_TABLE_NOT_FOUND,
	ERROR_REGISTER_NOT_FOUND,
	ERROR_TABLE_ALREADY_EXISTS
} e_lfs_operation_result;

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

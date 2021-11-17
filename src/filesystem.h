#define BASE_BLOCK_ADDRESS 100
#define FILENAME_LENGTH 256

typedef struct
{
	int head, tail;
} base_block_t;

typedef struct
{
	char filename[ FILENAME_LENGTH ];
	int next_file_address;
	char padding[ 252 ];
} metadata_t;

base_block_t *base_block;

void filesystem_init();
void create_file( char *, char * );

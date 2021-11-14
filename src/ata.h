#define BASE_PORT 0x1F0
#define SECTOR_SIZE 512

void *read_disk( int );
void write_disk( int, void * );

void *read_disk_chs( int );
void write_disk_chs( int, void * );

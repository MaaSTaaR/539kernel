#include "filesystem.h"

void filesystem_init()
{
	base_block = read_disk( BASE_BLOCK_ADDRESS );
	
	println();
	print( "BASE BLOCK = " );
	printi( base_block );
	println();
	printi( base_block->head );
	println();
	printi( base_block->tail );
	println();
}

void create_file( char *filename, char *buffer )
{
	int metadata_lba = BASE_BLOCK_ADDRESS + 1; //( base_block->head == 0 ) ? BASE_BLOCK_ADDRESS + 1 : base_block->tail + 1;
	int file_lba = metadata_lba + 1;
	
	metadata_t *metadata = kalloc( sizeof( metadata_t ) );
	
	printi( metadata );
	println();
	
	metadata->next_file_address = 0;
	
	// ... //
	
	int currIdx;
	
	for ( currIdx = 0; *filename != '\0' && currIdx < FILENAME_LENGTH - 1; currIdx++, filename++ )
		metadata->filename[ currIdx ] = *filename;
	
	metadata->filename[ currIdx ] = '\0';
	
	print( metadata->filename );
	
	
	
	//while( 1 );
	
	// ... //
	
	for ( currIdx = 0; currIdx < 252; currIdx++ )
		metadata->padding[ currIdx ] = 0;
	
	// ... //
	
	//write_disk( metadata_lba, metadata );
	println();
	printi( buffer );
	
	write_disk( metadata_lba, metadata );
	write_disk( file_lba, ( short * ) buffer );
	
	
	println();
	print( "WRITE DONE" );
	println();
	// ... //
	
	/*metadata->filename = { 'F', 'O', '\0' };
	metadata->number_of_blocks = 1;
	metadata->next_file_address = 0;
	
	// ... //
	
	void *raw_data = kalloc( sizeof( metadata_t ) + sizeof( *content ) );*/
}

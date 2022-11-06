#include "filesystem.h"

void filesystem_init()
{
	base_block = read_disk( BASE_BLOCK_ADDRESS );
}

void update_base_block( int new_head, int new_tail )
{
	base_block->head = new_head;
	base_block->tail = new_tail;
	
	write_disk( BASE_BLOCK_ADDRESS, base_block );
}

metadata_t *load_metadata( int address )
{
	metadata_t *metadata = read_disk( address );
	
	return metadata;
}

int get_files_number()
{
	if ( base_block->head == 0 )
		return 0;
	
	int files_number = 0;
	
	// ... //
	
	metadata_t *curr_file = load_metadata( base_block->head );
	
	while ( 1 )
	{
		files_number++;

		if ( curr_file->next_file_address == 0 )
			break;
		
		curr_file = load_metadata( curr_file->next_file_address );
	}
	
	return files_number;
}

void create_file( char *filename, char *buffer )
{
	int metadata_lba = ( base_block->head == 0 ) ? BASE_BLOCK_ADDRESS + 1 : base_block->tail + 2;
	int file_lba = metadata_lba + 1;
	
	metadata_t *metadata = kalloc( sizeof( metadata_t ) );
	
	metadata->next_file_address = 0;
	
	// ... //
	
	int currIdx;
	
	for ( currIdx = 0; *filename != '\0' && currIdx < FILENAME_LENGTH - 1; currIdx++, filename++ )
		metadata->filename[ currIdx ] = *filename;
	
	metadata->filename[ currIdx ] = '\0';
	
	// ... //
	
	write_disk( metadata_lba, metadata );
	write_disk( file_lba, buffer );
	
	// ... //
	
	if ( base_block->head == 0 )
	{
		update_base_block( metadata_lba, metadata_lba );
	}
	else
	{
		metadata_t *tail_metadata = load_metadata( base_block->tail );
		
		tail_metadata->next_file_address = metadata_lba;
		
		write_disk( base_block->tail, tail_metadata );		
		update_base_block( base_block->head, metadata_lba );
	}
}

char **list_files()
{
	if ( base_block->head == 0 )
		return -1;
	
	char **list;
	
	list = kalloc( get_files_number() * sizeof( char * ) );
		
	metadata_t *curr_file = load_metadata( base_block->head );
	
	int idx = 0;
	
	while ( 1 )
	{
		list[ idx ] = curr_file->filename;

		if ( curr_file->next_file_address == 0 )
			break;
		
		curr_file = load_metadata( curr_file->next_file_address );
		
		idx++;
	}
	
	return list;
}

int get_address_by_filename( char *filename )
{
	metadata_t *curr_file = load_metadata( base_block->head );
	int curr_file_address = base_block->head;
	
	int idx = 0;
	
	while ( 1 )
	{
		if ( strcmp( curr_file->filename, filename ) == 1 )
			return curr_file_address;
			
		if ( curr_file->next_file_address == 0 )
			break;
		
		curr_file_address = curr_file->next_file_address;
		curr_file = load_metadata( curr_file->next_file_address );		
	}
	
	return 0;
}

char *read_file( char *filename )
{
	int address = get_address_by_filename( filename );
	
	if ( address == 0 )
		return 0;
	
	printi( address );
	
	char *buffer = read_disk( address + 1 );
	
	return buffer;
}

int get_prev_file_address( int address )
{
	metadata_t *prev_file = load_metadata( base_block->head );
	int prev_file_address = base_block->head;

	while ( 1 )
	{
		if ( prev_file->next_file_address == address )
			return prev_file_address;
		
		prev_file_address = prev_file->next_file_address;
		prev_file = load_metadata( prev_file->next_file_address );
	}
		
	return -1;
}

void delete_file( char *filename )
{
	int curr_file_address = get_address_by_filename( filename );
	
	if ( curr_file_address == 0 )
		return;
		
	// ... //
	
	if ( get_files_number() == 1 )
	{
		update_base_block( 0, 0 );
		
		return;
	}
			
	metadata_t *curr_file_metadata = read_disk( curr_file_address );
	
	if ( curr_file_address == base_block->head )
	{
		update_base_block( curr_file_metadata->next_file_address, base_block->tail );
	}
	else
	{
		int prev_file_address = get_prev_file_address( curr_file_address );
		
		metadata_t *prev_file = load_metadata( prev_file_address );

		prev_file->next_file_address = curr_file_metadata->next_file_address;
		
		write_disk( prev_file_address, prev_file );
		
		if ( curr_file_address == base_block->tail )
			update_base_block( base_block->head, prev_file_address );
	}
}

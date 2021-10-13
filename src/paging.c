#include "paging.h"

void paging_init()
{
	// Initializing Kernel's Page Directory (1 to 1 mapping)
	
	int curr_frame_base = 0;
	
	page_directory = kalloc( 8 * 1024 );
	
	for ( int currPDE = 0; currPDE < 1024; currPDE++ )
	{
		int *pagetable = (int *) kalloc( 8 * 1024 );
		
		for ( int currPTE = 0; currPTE < 1024; currPTE++ )
		{
			pagetable[ currPTE ] = create_page_entry( curr_frame_base * 4096, 1, 0, 0, 1, 1, 0, 0, 0 );
			
			curr_frame_base++;
		}
		
		page_directory[ currPDE ] = create_page_entry( pagetable, 1, 0, 0, 1, 1, 0, 0, 0 );
	}
	
	// ... //
	
	// Enabling Paging
}

int create_page_entry( int base_address, char present, char writable, char privilege_level, char cache_enabled, char write_through_cache, char accessed, char page_size, char dirty )
{
	int entry = 0;
	
	entry |= present;
	entry |= writable << 1;
	entry |= privilege_level << 2;
	entry |= write_through_cache << 3;
	entry |= cache_enabled << 4;
	entry |= accessed << 5;
	entry |= dirty << 6;
	entry |= page_size << 7;
	entry |= base_address << 12;
	
	return entry;
}



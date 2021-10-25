#include "paging.h"

void paging_init()
{
	// Initializing Kernel's Page Directory (1 to 1 mapping)
	
	unsigned int curr_page_frame = 0;
	
	// We allocate 4 * 1024 bytes here, whatever the size of
	// the page directory, to make sure that the page tables
	// that are coming next are in page aligned-addresses.
	page_directory = kalloc( 4 * 1024 );
		
	for ( int currPDE = 0; currPDE < PDE_NUM; currPDE++ )
	{
		unsigned int *pagetable = kalloc( 4 * PTE_NUM );
		
		for ( int currPTE = 0; currPTE < PTE_NUM; currPTE++, curr_page_frame++ )
			pagetable[ currPTE ] = create_page_entry( curr_page_frame * 4096, 1, 0, 0, 1, 1, 0, 0, 0 );
		
		page_directory[ currPDE ] = create_page_entry( pagetable, 1, 0, 0, 1, 1, 0, 0, 0 );
	}

	// ... //
	
	load_page_directory();
	enable_paging();
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
	
	return base_address | entry;
}



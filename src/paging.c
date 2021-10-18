#include "paging.h"

#define PDE_NUM 2
#define PTE_NUM 1024

void paging_init()
{
	// Initializing Kernel's Page Directory (1 to 1 mapping)
	
	unsigned int curr_frame_base = 0;
	
	page_directory = kalloc( 4 * 1024 );//PDE_NUM );
		
	for ( int currPDE = 0; currPDE < PDE_NUM; currPDE++ )
	{
		//if ( currPDE > 10 )
			//while ( 1 );
	
		unsigned int *pagetable = kalloc( 4 * PTE_NUM );
		
		for ( int currPTE = 0; currPTE <= PTE_NUM; currPTE++ )
		{
			pagetable[ currPTE ] = ( curr_frame_base * 4096 ) | 25; //( ( curr_frame_base * 4096 ) ) | 25; //create_page_entry( curr_frame_base * 4096, 1, 0, 0, 1, 1, 0, 0, 0 );
			
			curr_frame_base++;
			
			//if ( curr_frame_base > 15 )
				//curr_frame_base = 0;
			
			//printi( curr_frame_base * 4096 );
			//println();
		}
		
		// Bochs bug??
		if ( currPDE == 1 ){ //( pagetable == 126 )
			pagetable = 0xF000;
			//printi( (unsigned int) pagetable );
		}
		
		page_directory[ currPDE ] = ( ( (unsigned int) pagetable ) ) | 25; //0xE000 | 25; // ( ( (unsigned int) pagetable ) ) | 25; //create_page_entry( pagetable, 1, 0, 0, 1, 1, 0, 0, 0 );
		
		//printi( (unsigned int) pagetable );
		//println();
		/*printi( page_directory[ currPDE ] );
		println();*/
	
		
	}
	
	// 4MB Page Size
	/*
	int curr_frame_base = 0;
	
	page_directory = kalloc( 4 * PDE_NUM );
		
	for ( int currPDE = 0; currPDE < PDE_NUM; currPDE++, curr_frame_base++ )
	{
		page_directory[ currPDE ] = create_page_entry( curr_frame_base * 4096, 1, 0, 0, 1, 1, 0, 1, 0 );
	}
	*/


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
	//entry |= base_address << 12;
	
	return ( base_address | entry );//entry;
}



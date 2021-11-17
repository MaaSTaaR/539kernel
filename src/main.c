#include "heap.h"
#include "paging.h"
#include "screen.h"
#include "scheduler.h"
#include "ata.h"
#include "filesystem.h"

void processA();
void processB();
void processC();
void processD();

void kernel_main()
{	
	heap_init();
	paging_init();	
	screen_init();
	process_init();
	scheduler_init();
	filesystem_init();
	
	// ... //
	
	print( "Welcome to 539kernel!" );
	println();
	print( "We are now in Protected-mode" );
	println();
	printi( 539 );
	println();
	
	// ... //
	
	char data[ 512 ] = "The content of the first file on 539filesystem";
	
	create_file( "first_file", data );
	
	/*void *data = //read_disk_chs( 1 ); 
				read_disk( 100 );
	
	printi( data );*/
	
	
	/*char *data = "AAAAAAAABBBBBBBB";
	
	write_disk( 100, data );*/
	
	// ... //
	
	/*int *data2 = ( int * ) read_disk( 1 );
	
	printi( data2 );*/
	
	
//	write_disk_chs( 1, data );
	/*
	println();
	print( "=============" );
	*/
	/*process_create( &processA );
	process_create( &processB );
	process_create( &processC );
	process_create( &processD );
	
	asm( "sti" );*/
	
	while( 1 );
}

void interrupt_handler( int interrupt_number )
{
	print( "Interrupt Received " );
	printi( interrupt_number );
	println();
}

void processA()
{
	print( "Process A," );

	while ( 1 )
		asm( "mov $5390, %eax" );
}

void processB()
{
	print( "Process B," );

	while ( 1 )
		asm( "mov $5391, %eax" );
}

void processC()
{
	print( "Process C," );

	while ( 1 )
		asm( "mov $5392, %eax" );
}

void processD()
{
	print( "Process D," );

	while ( 1 )
		asm( "mov $5393, %eax" );
}

#include "heap.h"
#include "paging.h"
#include "screen.h"
#include "scheduler.h"
#include "ata.h"
#include "filesystem.h"
#include "str.h"

void processA();
void processB();
void processC();
void processD();

void print_fs()
{
	char **files = list_files();

	for ( int currIdx = 0; currIdx < get_files_number(); currIdx++ )
	{
		print( "File: " );
		print( files[ currIdx ] );
		println();
	}
	
	print( "==" );
	println();
}

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
	
	char *data = kalloc( 512 );
	strcpy( data, "The content of the first file on 539filesystem" );	
	create_file( "first_file", data );
	
	// ... //
	
	char *data2 = kalloc( 512 );
	strcpy( data2, "SECOND FILE in 539filesystem" );
	create_file( "second_file", data2 );
	
	// ... //
	
	char *data3 = kalloc( 512 );
	strcpy( data3, "THIRD FILE in 539filesystem" );
	create_file( "third_file", data3 );
	
	// ... //
	
	char *data4 = kalloc( 512 );
	strcpy( data4, "FOURTH FILE in 539filesystem" );
	create_file( "fourth_file", data4 );
	
	// ... //
	
	//print_fs();
	
	//delete_file( "first_file" );
	//print_fs();
	
	//delete_file( "second_file" );
	//print_fs();
	
	//delete_file( "third_file" );
	//print_fs();
	
	//delete_file( "fourth_file" );
	//print_fs();
	

	
	
	// ... //
	
	print( read_file( "first_file" ) ); println();
	print( read_file( "second_file" ) ); println();
	print( read_file( "third_file" ) ); println();
	print( read_file( "fourth_file" ) ); println();
	
	// ... //
	

	
	/*void *data = //read_disk_chs( 1 ); 
				read_disk( 100 );
	
	printi( data );*/
	
	
	/*
	char *data = kalloc( 512 );
	
	for ( int currIdx = 0; currIdx < 512; currIdx++ )
		data[ currIdx ] = 'X';
	
	data[ 511 ] = 'D';
	
	write_disk( 0, data );

	char *data2 = kalloc( 512 );
	
	for ( int currIdx = 0; currIdx < 512; currIdx++ )
		data2[ currIdx ] = 'Y';
	
	data2[ 511 ] = 'D';
		
	write_disk( 1, data2 );
	
	char *data3 = kalloc( 512 );
	
	for ( int currIdx = 0; currIdx < 512; currIdx++ )
		data3[ currIdx ] = 'Z';
	
	data3[ 511 ] = 'D';
		
	write_disk( 2, data3 );
	
	read_disk( 0 );
	read_disk( 1 );
	read_disk( 2 );
	*/
	
	
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

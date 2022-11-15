#include "screen.h"
#include "scheduler.h"
#include "heap.h"

void processA();
void processB();
void processC();
void processD();

void print_fs();

void kernel_main()
{
	heap_init();
	paging_init();
	screen_init();
	process_init();
	scheduler_init();
	filesystem_init();
	
	print( "Welcome to 539kernel!" );
	println();
	print( "We are now in Protected-mode" );
	println();
	printi( 539 );
	println();
	
    process_create( &processA );
	process_create( &processB );
	process_create( &processC );
	process_create( &processD );
	
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
	
	print( read_file( "first_file" ) ); println();
	print( read_file( "second_file" ) ); println();
	print( read_file( "third_file" ) ); println();
	
	// ... //
	
	print_fs();
	delete_file( "first_file" );
	print_fs();

	// ... //
	
	while( 1 );
}

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

void interrupt_handler( int interrupt_number )
{
	//println();
	//print( "Interrupt Received " );
	//printi( interrupt_number );
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

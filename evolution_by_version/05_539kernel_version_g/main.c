#include "screen.h"
#include "scheduler.h"
#include "heap.h"

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
	
	while( 1 );
}

void interrupt_handler( int interrupt_number )
{
	println();
	print( "Interrupt Received " );
	printi( interrupt_number );
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

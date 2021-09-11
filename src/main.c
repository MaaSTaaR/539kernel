#include "screen.h"
#include "process.h"
#include "scheduler.h"

void processA();
void processB();
void processC();

void kernel_main()
{	
	process_t p1, p2, p3;
	
	// ... //
	
	screen_init();
	process_init();
	
	// ... //
	
	print( "Welcome to 539kernel!" );
	println();
	print( "We are now in Protected-mode" );
	println();
	printi( 539 );
	println();
	
	// ... //
	
	process_create( &processA, &p1 );
	process_create( &processB, &p2 );
//	process_create( &processC, &p3 );
	
//	while( 1 );
	
	asm( "sti" );
	
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
	print( "Process A" );
	println();	

	while ( 1 )
		asm( "mov $5390, %eax" );
}

void processB()
{
	print( "Process B" );
	println();	

	while ( 1 )
		asm( "mov $5391, %eax" );
}

void processC()
{
	print( "Process C" );
	println();	

	while ( 1 )
		asm( "mov $5392, %eax" );
}

#include "screen.h"
#include "process.h"
#include "scheduler.h"

void processA();
void processB();

void kernel_main()
{
	process_t p1, p2;
	
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
	
	/*
	print( "Processes Created" );
	println();
	printi( processes[ 0 ]->pid );
	println();
	printi( processes[ 1 ]->pid );
	println();
	*/
	
	while( 1 );
}

void interrupt_handler( int interrupt_number )
{
	print( "32 " );
	if ( interrupt_number == 32 )
		return;
	/*
	{
		scheduler();
		return;
	}*/
	
	println();
	print( "Interrupt Received " );
	printi( interrupt_number );
}

void processA()
{
	while ( 1 ) {
		print( "A1 " );
		println();
		print( "A2 " );
		println();
	}
}

void processB()
{
	while ( 1 ) {
		print( "B1 " );
		println();
		print( "B2 " );
		println();
	}
}

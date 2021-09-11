#include "screen.h"
#include "process.h"
#include "scheduler.h"

void processA();
void processB();

int cnt0 = 1;

void kernel_main()
{
	//asm( "cli" );
	
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
	
	//scheduler();
	
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

void interrupt_handler( /*int eip, int edi, int esi, int ebp, int esp, int ebx, int edx, int ecx, int eax,*/ int interrupt_number )
{
	//if ( cnt0 == 2 )
	//	asm( "l0: jmp l0" );
		
	/*print( "32 " );

	cnt0++;
	
	printi( cnt0 );
	
	if ( interrupt_number == 32 )
		return;		*/
	
	/*
	{
		scheduler();
		return;
	}*/
	
	/*
	if ( interrupt_number == 32 )
	{
		//printi( eip );
		//asm( "ihl: jmp ihl" );
		scheduler( eip, edi, esi, ebp, esp, ebx, edx, ecx, eax );
		return;
	}
	*/
	
	println();
	print( "Interrupt Received " );
	printi( interrupt_number );
	/*println();
	println();
	printi( eax );
	println();
	println();*/
}

void processA()
{
	/*asm( "cli" );
	print( "Process A" );
	asm( "mov $0x21b, %eax" );
	//asm( "l: jmp l" );
	asm( "sti" );*/
	
	//asm( "cli" );
	println();
	print( "Process A" );
	println();	
	//asm( "mov $539, %eax" );
	//asm( "l: jmp l" );
	//asm( "sti" );
	for ( int currIdx = 0; currIdx < 200; currIdx++ ) {
		print( "A" );
		printi( currIdx );
		print( " " );
	}
	asm( "l00: jmp l00" );
	
	/*
	while ( 1 ) {		
		print( "A" );
		println();
		print( "A1 " );
		println();
		print( "A2 " );
		println();
	}*/
}

void processB()
{
	//asm( "cli" );
	println();
	print( "Process B" );
	println();	
	//asm( "mov $5399, %eax" );
	//asm( "l: jmp l" );
	//asm( "sti" );
		for ( int currIdx = 0; currIdx < 200; currIdx++ ) {
		print( "B" );
		printi( currIdx );
		print( " " );
	}
	asm( "lb00: jmp lb00" );
	
	while ( 1 ) {
/*		print( "B1 " );
		println();
		print( "B2 " );
		println();*/
	}
}

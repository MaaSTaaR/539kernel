#include "process.h"

// VGA Text Mode = 0xB8000
// VGA Graphics Mode = 0xA0000
volatile unsigned char *video = 0xB8000;

int nextTextPos = 0;
int currLine = 0;

void print( char * );
void println();
void printi( int );

void processA();
void processB();

void kernel_main()
{
	process_t p1, p2;
	
	print( "Welcome to 539kernel!" );
	println();
	print( "We are now in Protected-mode" );
	println();
	printi( 539 );
	println();
	
	// ... //
	
	process_create( &processA, &p1 );
	process_create( &processB, &p2 );
	
	print( "Processes Created" );
	println();
	printi( processes[ 0 ]->pid );
	println();
	printi( processes[ 1 ]->pid );
	println();
	
	while( 1 );
}

void print( char *str )
{
	int currCharLocationInVidMem, currColorLocationInVidMem;
	
	while ( *str != '\0' )
	{
		currCharLocationInVidMem = nextTextPos * 2;
		currColorLocationInVidMem = currCharLocationInVidMem + 1;
		
		video[ currCharLocationInVidMem ] = *str;
		video[ currColorLocationInVidMem ] = 15;
		
		nextTextPos++;
		
		str++;
	}
}

void println()
{
	nextTextPos = ++currLine * 80;
}

void printi( int number )
{
	char* digitToStr[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	
	if ( number >= 0 && number <= 9 )
	{
		print( digitToStr[ number ] );
		return;
	}
	else
	{
		int remaining = number % 10;
		number = number / 10;
		
		printi( number );
		printi( remaining );
	}
}

void interrupt_handler( int interrupt_number )
{
	if ( interrupt_number == 32 )
	{
		scheduler();
		print( "SCH DONE " );
		return;
	}
	
	println();
	print( "Interrupt Received " );
	printi( interrupt_number );
}

void processA()
{
	while ( 1 )
		print( "Process A" );
}

void processB()
{
	while ( 1 )
		print( "Process B" );
}

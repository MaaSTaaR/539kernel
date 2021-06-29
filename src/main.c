// VGA Text Mode = 0xB8000
// VGA Graphics Mode = 0xA0000
volatile unsigned char *video = 0xB8000;

int textCurrPos = 0;
int lastStrSize = 0;

void print( char * );
void println();
void printi( int );

void kernel_main()
{
	print( "Welcome to 539kernel!" );
	println();
	print( "We are now in Protected-mode" );
	println();
	//printi( 0 );
	
	
	while( 1 );
}

void print( char *str )
{
	lastStrSize = 0;
	
	while ( *str != '\0' )
	{
		video[ textCurrPos++ ] = *str;
		video[ textCurrPos++ ] = 15;
		
		str++;
		lastStrSize += 2;
	}
}

void println()
{
	textCurrPos = ( textCurrPos - lastStrSize ) + 160;
}

/*
void printi( int number )
{
	asm( "l: jmp l" );
	
	char* digitToStr[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	
	//print( "0" );
	if ( number == 0 )
		print( digitToStr[ number ] );
		
	do {
		
	} while ( number > 10 );
}

*/

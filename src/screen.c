#include "screen.h"

void screen_init()
{
	// VGA Text Mode = 0xB8000
	// VGA Graphics Mode = 0xA0000
	video = 0xB8000;
	nextTextPos = 0;
	currLine = 0;
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
	if ( currLine > 23 )
	{
		cls();
		return;
	}
	
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

void cls()
{
	for ( int currPos = 0; currPos < 3999; currPos = currPos + 2 )
	{
		video[ currPos ] = 0;
		video[ currPos + 1 ] = 0;
	}
	
	nextTextPos = 0;
	currLine = 0;
	
}


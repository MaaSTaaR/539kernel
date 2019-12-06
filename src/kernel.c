//void print_c( char curr_char );
//char get_char();

asm(".code16gcc");

void main()
{
    // [MQH] 26 Nov 2019 
    // https://en.wikipedia.org/wiki/VGA-compatible_text_mode
    // It seems that video memory doesn't work in real mode. The details are here (https://forum.osdev.org/viewtopic.php?f=1&t=16333) need to read it.
	/*
	volatile char *video = (volatile char *) 0xB8000;
	
	*video++ = 's';
	*video++ = 15;
	*/
	
	// ... //
	
	// Since we are in Real Mode, inline assembly will be used until we move to Protected Mode.
    char curr_char_ = 'A';// = 'A';

	asm(    "movb $0x0E, %%ah\n"
	        "movb %0, %%al\n"
	        "int $0x10\n"
	        :
	        : "r" (curr_char_)
	        : "%al" );
	  
	print_c( (char) 'a' );
	
	while ( 1 );
	
	//print_char( (char) 'a' );
	//print_char( (char) 'a' );
	/*
	    curr_char_ = 'M';
	asm(    "movb $0x0E, %%ah\n"
	        "movb %0, %%al\n"
	        "int $0x10\n"
	        :
	        : "r" (curr_char_)
	        : "%al" );
	
	/*char curr_char = 'F';
		asm(    "movb $0x0E, %%ah\n"
	        "movb %0, %%al\n"
	        "int $0x10\n"
	        :
	        : "r" (curr_char)
	        : "%al" );*/
}

void print_c( char curr_char )
{
    char curr_char_ = 'S';
	asm(    "movb $0x0E, %%ah\n"
	        "movb %0, %%al\n"
	        "int $0x10\n"
	        :
	        : "r" (curr_char_)
	        : "%al" );
}

char get_char()
{
    return 'S';
}

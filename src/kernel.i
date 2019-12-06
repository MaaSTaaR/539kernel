# 1 "kernel.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "kernel.c"



asm(".code16gcc");

void main()
{
# 21 "kernel.c"
    char curr_char_ = 'A';

 asm( "movb $0x0E, %%ah\n"
         "movb %0, %%al\n"
         "int $0x10\n"
         :
         : "r" (curr_char_)
         : "%al" );

 print_c( (char) 'a' );

 while ( 1 );
# 52 "kernel.c"
}

void print_c( char curr_char )
{
    char curr_char_ = 'S';
 asm( "movb $0x0E, %%ah\n"
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

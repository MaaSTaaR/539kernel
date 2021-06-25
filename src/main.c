int main() 
{
	/*
	asm( "mov $0x0, %ah" );
	asm( "mov $0x03, %al" );
	asm( "int $0x10" );
	
	*/
	//*((int*)0xb8000)=0x07690748;
	
	//*((int*)0xb0000)=0x539;
	//asm( "movl $0x07690748,0xb8000" );
	//asm( "1: jmp 1" );
	
	//*((int*)0xb8000)=0x539;
	
	
	volatile unsigned char *video = 0xB8000;
	
	//video += 15;
	
	//video++;
	*video = (char) 0x41;
	video++;
	*video = (char) 0xf0;
	
	video++;
	*video = (char) 'A';
	video++;
	*video = (char) 0xf0;
	
	//p();
	
	while( 1 );
	
	//gdt_init();
	
	//asm( "1: jmp 1" );
	
	
	/*asm( "mov $0x0E, %ah" );
	asm( "mov $0x45, %al" );
	asm( "int $0x10" );*/
	
	//p();
	
	//asm( "1: jmp 1" );
	/*asm( "nop" );
	asm( "mov %cr0, %eax" );
	asm( "1: jmp 1" );
	
	//p();
	*/
	
	return 0;
}

void p()
{
	/*asm( "mov $0x0E, %ah" );
	asm( "mov $0x43, %al" );
	asm( "int $0x10" );
	asm( "mov $0x0E, %ah" );
	asm( "mov $0x43, %al" );
	asm( "int $0x10" );
	asm( "12: jmp 12" );*/
	while ( 1 );
}

/*
typedef struct
{
	unsigned short limit;
	unsigned short base_low;
	unsigned char base_mid;
	unsigned char access;
	unsigned char grand;
	unsigned char base_high;
} __attribute__((packed)) seg_descr_t;

struct gdt_ptr
{
	unsigned short size;
	unsigned long offset;
} __attribute__((packed));

#define GDT_ENTRIES 3

seg_descr_t gdt[ GDT_ENTRIES ];
struct gdt_ptr gdt_p;

void gdt_add( int num, int base, int limit, char access, char grand )
{
	gdt[ num ].base_low = base & 0xFFFF;
	gdt[ num ].base_mid = ( base >> 16 ) & 0xFF;
	gdt[ num ].base_high = ( base >> 24 ) & 0xFF;
	
	gdt[ num ].limit = limit & 0xFFFF;
	gdt[ num ].grand = ( limit >> 16 ) & 0x0F;
	
	gdt[ num ].grand |= grand & 0xF0;
	
	gdt[ num ].access |= access;
}

void gdt_init()
{
	gdt_p.size = ( sizeof( seg_descr_t ) * GDT_ENTRIES ) - 1;
	gdt_p.offset = (int) &gdt;
	
	// NULL Segment
	gdt_add( 0, 0, 0, 0, 0 );
	
	// Access flag (a byte) = 0x9A = 10011010
	// From the left :
	//		1 = Present bit, That's mean this is a vaild selector
	//		00 = Ring level ( 0 = Highest for the kernel )
	//		1 = Descriptor Type, That's mean this descriptor is a Code or Data Segment
	//		1010 = Segment Type
	gdt_add( 1, 0, 0xFFFFFFFF, 0x9A, 0xCF );
	gdt_add( 2, 0, 0xFFFFFFFF, 0x92, 0xCF );
	
	// Set the information in GDTR register.
	//load_gdtr( &gdt_p );
}
*/

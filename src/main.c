int main() 
{
	asm( "mov $0x0E, %ah" );
	asm( "mov $0x43, %al" );
	asm( "int $0x10" );
	
	asm( "mov $0x44, %al" );
	asm( "int $0x10" );
	
	return 0;
}

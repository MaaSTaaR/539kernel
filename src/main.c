/*void abc();
void cda();
int p();*/

//volatile unsigned char *video = 0x539;//0xB8000;

volatile unsigned char *video = 0xB8000;
//int num2 = 5;

int kernel_main()
{
	//asm( "l: jmp l" );
	
	//volatile unsigned int *g = 0x1A68;
	
	//*g = 6;
	
	//int sum = num1 + num2;
	
	int *p = &video;
	int p2 = video;
	
	//volatile unsigned char *video = 0xB8000;
	*video = (char) 'M';
	video++;
	*video = (char) 0xf1;
	
	abc();
	
	while( 1 );

	return 0;
}


void abc()
{
	//volatile unsigned char *video = 0xB8000;
	
	video++;
	*video = (char) 'F';
	video++;
	*video = (char) 0xf1;
}
/*
void cda()
{
	volatile unsigned char *video = 0xB8000;

//	video++;
	*video = (char) 'T';
	video++;
	*video = (char) 0xf1;

}

int p()
{
	cda();
	return 0;
}
*/

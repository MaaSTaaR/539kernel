#include "ata.h"

void read_disk()
{
	/*dev_write( 0x1f6, 0x0a0 );
	dev_write( 0x1f2, 1 );
	dev_write( 0x1f3, 1 );
	dev_write( 0x1f4, 0 );
	dev_write( 0x1f5, 0 );
	dev_write( 0x1f7, 0x20 );*/
	
	// Read the status
	int status = 0;
	
	do
	{
		status = dev_read( 0x1f7 );
	} while ( status >= 8 );
}

void write_disk()
{
}



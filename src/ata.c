#include "ata.h"

#define ATA_BASE 0x1F0
//QEMU: 0x1E8

void *ata_buffer;

void read_disk()
{
	/*ata_buffer = kalloc( 512 );
	
	test_ata();
	
	println();
	printi( ata_buffer );
	
	return;*/
	
	dev_write( ATA_BASE + 6, 0x0a0 ); // Drive 0 and Head 0
	dev_write( ATA_BASE + 2, 1 ); // Sector count
	
	dev_write( ATA_BASE + 3, 1 ); // Sector to read
	
	dev_write( ATA_BASE + 4, 0 ); // Cylinder - Low

	dev_write( ATA_BASE + 5, 0 ); // Cylinder - High
	
	dev_write( ATA_BASE + 7, 0x20 ); // Command: Read with Retry
	
	ata_finished_read();
	
	//still_going();
	
	/*printi( dev_read( ATA_BASE + 7 ) );
	println();
	printi( dev_read( ATA_BASE + 7 ) );
	println();
	while ( 1 );*/
	
	
	// Read the status
	
	/*int status = 0;
	
	do
	{
		status = dev_read( ATA_BASE + 7 );
		
		
		printi( status );
		println();
		
		if ( status == 1 )
		{
			int error_code = dev_read( ATA_BASE + 1 );
			
			print( "Err Code " );
			printi( error_code );
			
			while ( 1 );
		}
		else if ( status != 0 )
		{
			printi( status );
			println();
			
			//while ( 1 );
		}
		
	} while ( status < 128 ); //( status >> 7 ) != 1 );
	
	println();
	print( "===========" );
	printi( status );
	*/
	print( "===========" );
	while ( 1 );
}

void write_disk()
{
}



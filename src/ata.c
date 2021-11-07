#include "ata.h"

#define ATA_BASE 0x1F0
#define SECTOR_SIZE 512

void *ata_buffer;

void *read_disk( int sector )
{
	void *buffer = kalloc( SECTOR_SIZE );
	
	// ... //
	
	dev_write( ATA_BASE + 6, 0x0a0 ); // Drive 0 and Head 0
	dev_write( ATA_BASE + 2, 1 ); // Sector count
	dev_write( ATA_BASE + 3, sector ); // Sector to read
	dev_write( ATA_BASE + 4, 0 ); // Cylinder - Low
	dev_write( ATA_BASE + 5, 0 ); // Cylinder - High
	dev_write( ATA_BASE + 7, 0x20 ); // Command: Read with Retry
	
	int status = 0;
	
	do
	{
		status = dev_read( ATA_BASE + 7 ) ;
	} while ( ( status ^ 0x80 ) == 128 );
	
	// ... //
	
	ata_copy_to_buffer( ATA_BASE, SECTOR_SIZE / 2, buffer );
	
	return buffer;
}

void write_disk( int sector, void *buffer )
{
	dev_write( ATA_BASE + 6, 0x0a0 ); // Drive 0 and Head 0
	dev_write( ATA_BASE + 2, 1 ); // Sector count
	dev_write( ATA_BASE + 3, sector ); // Sector to read
	dev_write( ATA_BASE + 4, 0 ); // Cylinder - Low
	dev_write( ATA_BASE + 5, 0 ); // Cylinder - High
	dev_write( ATA_BASE + 7, 0x30 ); // Command: Write with Retry
	
	int status = 0;
	
	do
	{
		status = dev_read( ATA_BASE + 7 ) ;
	} while ( ( status ^ 0x80 ) == 128 );
	
	// ... //
	
	ata_copy_to_disk( ATA_BASE, SECTOR_SIZE / 2, buffer );
}



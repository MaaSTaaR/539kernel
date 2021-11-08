#include "ata.h"

#define ATA_BASE 0x1F0
#define SECTOR_SIZE 512

// LBA
void *read_disk( int address )
{
	void *buffer = kalloc( SECTOR_SIZE );
	
	// ... //
	
	dev_write( ATA_BASE + 6, ( 0x0e0 | ( ( address & 0x0F000000 ) >> 24 ) ) ); // Drive 0. Bits 0-3 = Bits 24-27 of LBA
	dev_write( ATA_BASE + 2, 1 ); // Sector count
	dev_write( ATA_BASE + 3, address & 0x000000FF ); // LBA's 0-7 bits
	dev_write( ATA_BASE + 4, ( address & 0x0000FF00 ) >> 8 ); // LBA's 8-15 bits
	dev_write( ATA_BASE + 5, ( address & 0x00FF0000 ) >> 16 ); // LBA's 16-23 bits
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

// LBA
void write_disk( int address, void *buffer )
{
	dev_write( ATA_BASE + 6, ( 0x0e0 | ( ( address & 0x0F000000 ) >> 24 ) ) ); // Drive 0. Bits 0-3 = Bits 24-27 of LBA
	dev_write( ATA_BASE + 2, 1 ); // Sector count
	dev_write( ATA_BASE + 3, address & 0x000000FF ); // LBA's 0-7 bits
	dev_write( ATA_BASE + 4, ( address & 0x0000FF00 ) >> 8 ); // LBA's 8-15 bits
	dev_write( ATA_BASE + 5, ( address & 0x00FF0000 ) >> 16 ); // LBA's 16-23 bits
	dev_write( ATA_BASE + 7, 0x30 ); // Command: Write with Retry
	
	int status = 0;
	
	do
	{
		status = dev_read( ATA_BASE + 7 ) ;
	} while ( ( status ^ 0x80 ) == 128 );
	
	// ... //
	
	ata_copy_to_disk( ATA_BASE, SECTOR_SIZE / 2, buffer );
}


void *read_disk_chs( int sector )
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

void write_disk_chs( int sector, void *buffer )
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



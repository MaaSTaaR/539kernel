#include "ata.h"

// LBA
void *read_disk( int address )
{
	dev_write( BASE_PORT + 6, ( 0x0e0 | ( ( address & 0x0F000000 ) >> 24 ) ) ); // Drive 0. Bits 0-3 = Bits 24-27 of LBA
	dev_write( BASE_PORT + 2, 1 ); // Sector count
	dev_write( BASE_PORT + 3, address & 0x000000FF ); // LBA's 0-7 bits
	dev_write( BASE_PORT + 4, ( address & 0x0000FF00 ) >> 8 ); // LBA's 8-15 bits
	dev_write( BASE_PORT + 5, ( address & 0x00FF0000 ) >> 16 ); // LBA's 16-23 bits
	dev_write( BASE_PORT + 7, 0x20 ); // Command: Read with Retry
	
	// ... //
		
	int status = 0;
	
	do
	{
		status = dev_read( BASE_PORT + 7 ) ;
	} while ( ( status ^ 0x80 ) == 128 );
	
	// ... //
	
	short *buffer = kalloc( SECTOR_SIZE );
	
	for ( int currByte = 0; currByte < ( SECTOR_SIZE / 2 ); currByte++ )
		buffer[ currByte ] = dev_read( BASE_PORT );
	
	return buffer;
}

// LBA
void write_disk( int address, short *buffer )
{	
	dev_write( BASE_PORT + 6, ( 0x0e0 | ( ( address & 0x0F000000 ) >> 24 ) ) ); // Drive 0. Bits 0-3 = Bits 24-27 of LBA
	dev_write( BASE_PORT + 2, 1 ); // Sector count
	dev_write( BASE_PORT + 3, address & 0x000000FF ); // LBA's 0-7 bits
	dev_write( BASE_PORT + 4, ( address & 0x0000FF00 ) >> 8 ); // LBA's 8-15 bits
	dev_write( BASE_PORT + 5, ( address & 0x00FF0000 ) >> 16 ); // LBA's 16-23 bits
	dev_write( BASE_PORT + 7, 0x30 ); // Command: Write with Retry
	
	//int status = 0;
	
	do
	{
		status = dev_read( BASE_PORT + 7 ) ;
	} while ( ( status ^ 0x80 ) == 128 );
	
	// ... //
	
	for ( int currByte = 0; currByte < ( SECTOR_SIZE / 2 ); currByte++ )
		dev_write_word( BASE_PORT, buffer[ currByte ] );
}


void *read_disk_chs( int sector )
{
	dev_write( BASE_PORT + 6, 0x0a0 ); // Drive 0 and Head 0
	dev_write( BASE_PORT + 2, 1 ); // Sector count
	dev_write( BASE_PORT + 3, sector ); // Sector to read
	dev_write( BASE_PORT + 4, 0 ); // Cylinder - Low
	dev_write( BASE_PORT + 5, 0 ); // Cylinder - High
	dev_write( BASE_PORT + 7, 0x20 ); // Command: Read with Retry
	
	int status = 0;
	
	do
	{
		status = dev_read( BASE_PORT + 7 );
	} while ( ( status ^ 0x80 ) == 128 );
	
	// ... //
	
	short *buffer = kalloc( SECTOR_SIZE );
	
	for ( int currByte = 0; currByte < ( SECTOR_SIZE / 2 ); currByte++ )
		buffer[ currByte ] = dev_read( BASE_PORT );

	return buffer;
}

void write_disk_chs( int sector, short *buffer )
{
	dev_write( BASE_PORT + 6, 0x0a0 ); // Drive 0 and Head 0
	dev_write( BASE_PORT + 2, 1 ); // Sector count
	dev_write( BASE_PORT + 3, sector ); // Sector to read
	dev_write( BASE_PORT + 4, 0 ); // Cylinder - Low
	dev_write( BASE_PORT + 5, 0 ); // Cylinder - High
	dev_write( BASE_PORT + 7, 0x30 ); // Command: Write with Retry
	
	int status = 0;
	
	do
	{
		status = dev_read( BASE_PORT + 7 ) ;
	} while ( ( status ^ 0x80 ) == 128 );
	
	// ... //
	
	for ( int currByte = 0; currByte < ( SECTOR_SIZE / 2 ); currByte++ )
		dev_write_word( BASE_PORT, buffer[ currByte ] );
}



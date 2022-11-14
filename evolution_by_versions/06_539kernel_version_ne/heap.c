#include "heap.h"

void heap_init()
{
	heap_base = 0x100000;
}

int kalloc( int bytes )
{
	unsigned int new_object_address = heap_base;
	
	heap_base += bytes;
	
	return new_object_address;
}

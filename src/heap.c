#include "heap.h"

void heap_init()
{
	heap_base = 0xE000;
}

void *kalloc( int bytes )
{
	void *new_object_address = heap_base;
	
	heap_base += bytes;
	
	return new_object_address;
}

#include "scheduler.h"
#include "process.h"

int next_sch_pid = 0;
int curr_sch_pid = 0;

process_t *get_next_process()
{
	printi( next_sch_pid );
	
	process_t *next_process = processes[ next_sch_pid ];
	
	curr_sch_pid = next_sch_pid;
	next_sch_pid++;
	next_sch_pid = next_sch_pid % processes_count;
	
	return next_process;
}

void scheduler()
{
	//print( "SCH" );
	//while ( 1 );
	
	asm( "cli" );
	
	process_t *next_process = get_next_process();
	
	 asm volatile("         \
     mov %0, %%ecx;       \
     sti;                 \
     jmp *%%ecx           "
                : : "r"(next_process->context.eip));
}

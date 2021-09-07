#include "process.h"

int processes_count = 0;
int curr_pid = 0;
int next_sch_pid = 0;
int curr_sch_pid = 0;

void process_create( int *base_address, process_t *process )
{
	process->pid = curr_pid++;
	
	process->context.eax = 0;
	process->context.ecx = 0;
	process->context.edx = 0;
	process->context.ebx = 0;
	process->context.esp = 0;
	process->context.ebp = 0;
	process->context.esi = 0;
	process->context.edi = 0;
	process->context.eip = base_address;
	
	process->state = READY;
	process->base_address = base_address;
	
	processes[ process->pid ] = process;
	
	processes_count++;
}

void scheduler()
{
	process_t curr_process = processes[ curr_sch_pid ];	
	process_t next_process = processes[ next_sch_pid ];
	
	curr_sch_pid = next_sch_pid;
	
	next_sch_pid++;
	next_sch_pid = next_sch_pid % processes_count;
}

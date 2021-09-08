#include "scheduler.h"
#include "process.h"

int next_sch_pid = 0;
int curr_sch_pid = 0;

int cnt = 0;

process_t *get_next_process()
{
	process_t *next_process = processes[ next_sch_pid ];
	
	curr_sch_pid = next_sch_pid;
	next_sch_pid++;
	next_sch_pid = next_sch_pid % processes_count;
	
	return next_process;
}

void copy_process_context( process_t *process )
{
	/*println();
	print( "CPY" );
	println();
	
	process->context.eax = 123;
	
	printi( process->context.eax );
	println();*/
	
	asm( "	mov %%eax, %0;       \
			mov %%ecx, %1;       \
			mov %%edx, %2;       \
			mov %%ebx, %3;       \
			mov %%esp, %4;       \
			mov %%ebp, %5;       \
			mov %%esi, %6;       \
			mov %%edi, %7;"
				: 	"=g" ( process->context.eax ), "=g" ( process->context.ecx ), "=g" ( process->context.edx ), "=g" ( process->context.ebx ), "=g" ( process->context.esp ),
					"=g" ( process->context.ebp ), "=g" ( process->context.esi ), "=g" ( process->context.edi ) );
					
	printi( process->context.eax );
	
	println();
	print( "CPY" );
	println();
}

void scheduler()
{
	int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	
	asm( "cli" );
	//asm( "pusha" );
	//asm( "ll0: jmp ll0" );
	//asm( "	mov %%eax, %0;" : "=g" ( eax ) );
	
	//printi( eax );
	//println();
	//println();
	
	//asm( "ll0: jmp ll0" );
	cnt++;
	
	println();
	print( "---> CNT = " );
	printi( cnt );
	println();
	print( "===" );
	printi( eax );
	println();
		
	process_t *curr_process = processes[ curr_sch_pid ];
	process_t *next_process = get_next_process();
	
	if ( curr_process->state == RUNNING )
		copy_process_context( curr_process );
	
	curr_process->state = READY;
	next_process->state = RUNNING;
	
	if ( cnt == 2 )
		asm( "ll: jmp ll" );
	
	asm( "mov %0, %%ecx;	\
			sti;			\
	 		jmp *%%ecx" : : "r" ( next_process->context.eip ) );
}

#include "process.h"

int next_sch_pid, curr_sch_pid;

process_t *next_process;

void scheduler_init();
void scheduler( int, int, int, int, int, int, int, int, int );
void run_next_process();

#include "process.h"

int next_sch_pid, curr_sch_pid;

process_t *curr_process;

void scheduler_init();
void scheduler();
void run_next_process();

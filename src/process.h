struct process_context
{
	int eax;
};

struct process 
{
	struct process_context context;
	int pid 
};

void process_create();

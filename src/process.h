#ifndef __PROCESS_H__
#define __PROCESS_H__

#define MAX_PROCESS_NUM 3
#define MAX_TIME 50
#define MAX_PRIORITY 20
#define MAX_CPU_BURST 10
#define MAX_IO_BURST 5

// custom process template for simulation
typedef struct process
{
	int pid;

	// randomly generated attributes
	int arrival;
	int cpu_burst;
	int priority;
	int io_burst;
	int io_start; // cpu_time before i/o interrupt occurs

	// parameters for execution
	int cpu_remaining;
	int io_remaining;

	// parameters for evaluation
	int fst_arrival;
	int exec_start;
	int exec_end;
} Process;

Process* generate_process(int pid, int exp_burst);
int expdist_generate(int max_v);

#endif

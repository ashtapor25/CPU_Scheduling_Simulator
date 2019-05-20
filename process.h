#ifndef __PROCESS_H__
#define __PROCESS_H__

#define MAX_PROCESS_NUM 5
#define MAX_TIME 50
#define MAX_PRIORITY 20
#define MAX_CPU_BURST 20
#define MAX_IO_BURST 10

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
	int exec_start;
	int exec_end;
} Process;

Process* generate_process(int pid);

#endif

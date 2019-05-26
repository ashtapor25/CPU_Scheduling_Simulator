# CPU_Scheduling_Simulator
This is a CPU Scheduling Simulator Project for COSE341(Operating Systems) @Korea University

The program generates processes with random attributes assigned to them.
Attributes : arrival, cpu_burst, io_burst, io_start(cpu time required before the i/o interrupt occurs), priority

As cpu burst empirically shows a exponential distribution in real systems, I have added a mode to generate cpu_burst times following a exponential distribution. If you wish to use the exponential mode, MAX_CPU_BURST is recommended to be under 60 due to prevent overflows.
Also, please assign enough MAX_TIME to make all the processes be executed in time or else the evaluation will be tainted. You can play around with the variables in the process.h file for robust simulations.

6 algorithms are used to simulate the cpu scheduling.
Algorithms: 
1. First Come First Serverd, 
2. Non-preemptive Shortest Job First
3. Preemptive Shortest Job First
4. Non-preemptive Priority
5. Preemptie Priority
6. Round Robin

Gantt charts are displayed 50 clocks per line. 'idl' in the chart signifies that the cpu is idle.

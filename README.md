# CPU Scheduling
CPU scheduling is a process which allows one process to use the CPU whilethe execution of another process is on hold(in waiting state) due to unavail-ability of any resource like I/O etc, thereby making full use of CPU. The aimof CPU scheduling is to make the system efficient, fast and fair.Whenever the CPU becomes idle, the operating system must select oneof the processes in the ready queue to be executed.  The selection process iscarried out by the short-term scheduler (or CPU scheduler).  The schedulerselects from among the processes in memory that are ready to execute, andallocates the CPU to one of them

## How to Run
- chmod +x run.sh
- ./run.sh filename speed
e.g.
    `./run.sh test_cases/test_case_0.dat 10.0`

## How to generate new random Test Cases
./run.sh -gt
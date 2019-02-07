#ifndef STRUCTURES_H
#define STRUCTURES_H

#include<vector>
using namespace std;

#define FCFS 0
#define SJF 1
#define ROUNDROBIN 2
#define LOTTERY 3
#define PRIORITY 4
#define MLFQ 5

extern float speed;
extern int algo;

struct job {
    char type;
    int burst_time;
};

struct process {
    int pid;
    int priority;
    int arrival_time;
    int share;
    int waiting_time;
    bool mark;
    int custom_priority;
    vector<job> jobs;
};

bool compare_priority(process a, process b) { return (a.priority < b.priority); }
bool compare(process a, process b) { return (a.arrival_time < b.arrival_time); }
bool compare_bursttime(process a, process b) { return (a.jobs[0].burst_time < b.jobs[0].burst_time); }


#endif
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include<vector>
using namespace std;


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
    vector<job> jobs;
};

bool compare_priority(process a, process b) { return (a.priority < b.priority); }
bool compare(process a, process b) { return (a.arrival_time < b.arrival_time); }


#endif
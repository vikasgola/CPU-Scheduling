#ifndef PRINT_H
#define PRINT_H

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "structures.h"

using namespace std;

float speed;
int algo;

#define print(a) cout << a

template <typename T>
void table(vector<T> cpu, vector<T> inp, vector<T> out, vector<T> comp, int clk = -1) {
    
    system("clear");
    print("\033[1;31m");
    switch(algo){
        case FCFS:
            print("===== First Come First Serve Scheduling =====");
            break;
        case PRIORITY:
            print("===== Priority Scheduling =====");
            break;
        case SJF:
            print("===== Smallest Job First Scheduling =====");
            break;
        case LOTTERY:
            print("===== Lottery Scheduling =====");
            break;
        case ROUNDROBIN:
            print("===== Round Robin Scheduling =====");
            break;
        case MLFQ:
            print("===== Multilevel Feedback Queue Scheduling =====");
            break;
        default:
            break;
    }
    print("\n\033[0m");
    
    if(clk != -1){
        print("\t    \033[1;32m clock: "+to_string(clk)+"\t\n");
        print("\033[0m");
    }

    int max_len =
        max(max(max(cpu.size(), inp.size()), out.size()), comp.size());
    if(max_len > 0){
        print("\033[1;33m CPU\t INPUT\t OUTPUT\t COMPLETED\n\033[0m");
    }

    for (int i = 0; i < max_len; i++) {
        if (i < cpu.size()) {
            if (cpu[i].mark) print("\033[1;36m");
            print(cpu[i].pid);
            print("\t\033[0m");
        } else {
            print("-\t");
        }
        if (i < inp.size()) {
            if (inp[i].mark) print("\033[1;36m");
            print(inp[i].pid);
            print("\t\033[0m");
        } else {
            print("-\t");
        }
        if (i < out.size()) {
            if (out[i].mark) print("\033[1;36m");
            print(out[i].pid);
            print("\t\033[0m");
        } else {
            print("-\t");
        }
        if (i < comp.size()) {
            print("\033[1;32m");
            print(comp[i].pid);
            print("\t\033[0m");
        } else {
            print("-\t");
        }
        print("\n");
    }
    print("\033[1;31m ===== ===== ===== ===== ===== =====\033[0m\n");


    usleep(speed);
}

#endif
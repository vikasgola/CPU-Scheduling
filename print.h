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

void showProcess(vector<process> t, int check){
    if (check < t.size()) {
        if (t[check].mark) 
            print("\033[1;36m");
        print(t[check].pid);
        print("\t  \033[0m");
    } else {
        print("-\t  ");
    }
}

template <typename T>
void table(vector<T> cpu, vector<T> inp, vector<T> out, vector<T> comp, int clk = -1) {
    int aveage_wait_time = 0, average_n = 0;

    system("clear");
    print("\033[1;31m");
    switch(algo){
        case FCFS:
            print("=============== First Come First Serve Scheduling ===============");
            break;
        case PRIORITY:
            print("=============== Priority Scheduling ===============");
            break;
        case SJF:
            print("=============== Smallest Job First Scheduling ===============");
            break;
        case LOTTERY:
            print("=============== Lottery Scheduling ===============");
            break;
        case ROUNDROBIN:
            print("=============== Round Robin Scheduling ===============");
            break;
        case MLFQ:
            print("=============== Multilevel Feedback Queue Scheduling ===============");
            break;
        default:
            break;
    }
    print("\n\033[0m");
    
    if(clk != -1){
        print("\t\t   \033[1;32m ============ \t\n");
        print("\t\t   \033[1;32m   clock: "+to_string(clk)+"\t\n");
        print("\t\t   \033[1;32m ============ \t\n");
        print("\033[0m");
    }

    int max_len =
        max(max(max(cpu.size(), inp.size()), out.size()), comp.size());
    if(max_len > 0){
        print("\033[1;33m CPU\t INPUT\t OUTPUT\t COMPLETED\t TOTAL_WAIT_TIME\n\033[0m");
    }

    for (int i = 0; i < max_len; i++) {
        showProcess(cpu, i);
        showProcess(inp, i);
        showProcess(out, i);
        showProcess(comp, i);

        print("\t\t");
        if (i < comp.size()) {
            print(comp[i].waiting_time);
            aveage_wait_time += comp[i].waiting_time;
            average_n += 1;
        } else {
            print("-\t");
        }

        
        print("\n");
    }
    print("\033[1;33m ===== ===== ===== ===== ===== ===== ===== ===== =====\033[0m\n");
    
    print("\t\t   \033[1;32m ============ \t\n");
    print("\t\t   \033[1;32m  Statistics \t\n");
    print("\t\t   \033[1;32m ============ \t\n");
    print("\033[0m");
    if(average_n != 0){
        print("\033[1;33mTotal Jobs Done: \033[0m"<<average_n<<"\n");
        print("\033[1;33mAverage Waiting Time: \033[0m"<<(float)aveage_wait_time/average_n<<"\n");
    }else{
        print("\033[1;33mTotal Jobs Done: \033[0m"<<"-\n");
        print("\033[1;33mAverage Waiting Time: \033[0m"<<"-\n");
    }
    
    print("\033[1;31m ===== ===== ===== ===== ===== ===== ===== ===== ===== =====\033[0m\n");
    usleep(speed);
}

#endif
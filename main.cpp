#include "fcfs.h"
#include "print.h"
#include "priority.h"
#include "sjf.h"
#include "roundrobin.h"
#include "lottery.h"
#include "read.h"
#include "structures.h"

int clk = 0;
vector<process> process_CPU, process_input, process_output, process_completed;

void input() {
    fcfs(process_input, process_completed, process_CPU, process_input,
         process_output, clk);
}

void output() {
    fcfs(process_output, process_completed, process_CPU, process_input,
         process_output, clk);
}

void CPU() {
    switch(algo){
        case FCFS:
            fcfs(process_CPU, process_completed, process_CPU, process_input, process_output, clk);
            break;
        case PRIORITY:
            priority(process_CPU, process_completed, process_CPU, process_input, process_output, clk);
            break;
        case SJF:
            sjf(process_CPU, process_completed, process_CPU, process_input, process_output, clk);
            break;
        case LOTTERY:
            lottery(process_CPU, process_completed, process_CPU, process_input, process_output, clk);
            break;
        case ROUNDROBIN:
            roundrobin(process_CPU, process_completed, process_CPU, process_input, process_output, clk);
            break;
        case MLFQ:
            roundrobin(process_CPU, process_completed, process_CPU, process_input, process_output, clk);
            break;
        default:
            break;
    }
    lottery(process_CPU, process_completed, process_CPU, process_input, process_output, clk);
}

void startProcessing(vector<process> &tprocess_list) {
    print("==== Available ALgorithms ====\n");
    print("==============================\n");
    print("FCFS: 0\t\tSJF 1\nROUNDROBIN 2\tLOTTERY 3\nPRIORITY 4\tMLFQ 5\n");
    print("Select Scheduling Algorithms: ");
    cin>>algo;
    if(algo > 5){
        perror("Wrong Input");
        exit(EXIT_FAILURE);
    }

    while(!tprocess_list.empty() || !process_CPU.empty() ||
           !process_input.empty() || !process_output.empty()) {
            if (!tprocess_list.empty() && tprocess_list[0].arrival_time == clk) {
                if (tprocess_list[0].jobs[0].type == 'C') {
                    process_CPU.push_back(tprocess_list[0]);
                } else if (tprocess_list[0].jobs[0].type == 'I') {
                    process_input.push_back(tprocess_list[0]);
                } else if (tprocess_list[0].jobs[0].type == 'O') {
                    process_output.push_back(tprocess_list[0]);
                }

                tprocess_list.erase(tprocess_list.begin());
                if(tprocess_list[0].arrival_time == clk) continue;
                table(process_CPU, process_input, process_output, process_completed, clk);
            }
            input();
            output();
            CPU();
            table(process_CPU, process_input, process_output, process_completed, clk);
            clk++;
    }
    table(process_CPU, process_input, process_output, process_completed, clk);
}

// ./a.out speed
int main(int argc, char *argv[]) {
    vector<process> process_list = readFile("test.dat");
    vector<process> tprocess_list(process_list);
    if(argc == 2){
        speed = 1000000/stof(argv[1]);   
    }else{
        speed = 1000000/4.0;
    }

    startProcessing(tprocess_list);
    return 0;
}

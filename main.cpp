#include "fcfs.h"
#include "print.h"
#include "priority.h"
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
    priority(process_CPU, process_completed, process_CPU, process_input,
             process_output, clk);
}

void startProcessing(vector<process> &tprocess_list) {
    while (!tprocess_list.empty() || !process_CPU.empty() ||
           !process_input.empty() || !process_output.empty()) {
        if (!tprocess_list.empty() && tprocess_list[0].arrival_time == clk) {
            if (tprocess_list[0].jobs[0].type == 'C') {
                process_CPU.push_back(tprocess_list[0]);
                cout << "pushed CPU" << endl;
            } else if (tprocess_list[0].jobs[0].type == 'I') {
                process_input.push_back(tprocess_list[0]);
            } else if (tprocess_list[0].jobs[0].type == 'O') {
                process_output.push_back(tprocess_list[0]);
            }

            table(process_CPU, process_input, process_output, process_completed, clk);
            tprocess_list.erase(tprocess_list.begin());
        }
        input();
        output();
        CPU();
        clk++;
    }
    table(process_CPU, process_input, process_output, process_completed, clk);
}

int main(int argc, char *argv[]) {
    vector<process> process_list = readFile("test.dat");
    vector<process> tprocess_list(process_list);

    startProcessing(tprocess_list);
    return 0;
}

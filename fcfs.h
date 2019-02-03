#ifndef FCFS_H
#define FCFS_H
#include <unistd.h>
#include <vector>
#include<algorithm>
#include "print.h"
#include "structures.h"

void fcfs(vector<process> &work, vector<process> &process_completed,
          vector<process> &process_CPU, vector<process> &process_input,
          vector<process> &process_output, int &clk) {
    if (!work.empty()) {
        work[0].mark = true;
        work[0].jobs[0].burst_time--;
        table(process_CPU, process_input, process_output, process_completed, clk);
        if (work.size() > 1) {
            for (int i = 1; i < work.size(); i++) {
                work[i].waiting_time++;
            }
        }
        if (work[0].jobs[0].burst_time == 0) {
            job temp = work[0].jobs[0];
            work[0].jobs.erase(work[0].jobs.begin());
            work[0].arrival_time = clk;
            work[0].mark = false;

            if (!work[0].jobs.empty()) {
                if (work[0].jobs[0].type == 'C') {
                    process_CPU.push_back(work[0]);
                    sort(process_CPU.begin(), process_CPU.end(), compare);
                } else if (work[0].jobs[0].type == 'I') {
                    process_input.push_back(work[0]);
                    sort(process_input.begin(), process_input.end(), compare);
                } else if (work[0].jobs[0].type == 'O') {
                    process_output.push_back(work[0]);
                    sort(process_output.begin(), process_output.end(), compare);
                }
            }
            table(process_CPU, process_input, process_output, process_completed, clk);
            work.erase(work.begin());
        }
        table(process_CPU, process_input, process_output, process_completed, clk);
    }
}

#endif
#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H
#include <unistd.h>
#include <algorithm>
#include <vector>
#include "print.h"
#include "structures.h"

void roundrobin(vector<process> &work, vector<process> &process_completed,
                vector<process> &process_CPU, vector<process> &process_input,
                vector<process> &process_output, int &clk, int MAX_ROBIN) {
    static int working_on = 0;
    static int round_robin_time = 0;
    if (!work.empty()) {
        work[working_on].mark = true;
        work[working_on].jobs[0].burst_time--;
        table(process_CPU, process_input, process_output, process_completed,
              clk);
        work[working_on].mark = false;

        if (work.size() > 1) {
            for (int i = 1; i < work.size(); i++) {
                work[i].waiting_time++;
            }
        }
        if (work[working_on].jobs[0].burst_time == 0) {
            process temp = work[working_on];
            work[working_on].jobs.erase(work[working_on].jobs.begin());
            work[working_on].arrival_time = clk;

            if (!work[working_on].jobs.empty()) {
                if (work[working_on].jobs[0].type == 'C') {
                    process_CPU.push_back(work[working_on]);
                } else if (work[working_on].jobs[0].type == 'I') {
                    process_input.push_back(work[working_on]);
                    sort(process_input.begin(), process_input.end(), compare);
                } else if (work[working_on].jobs[0].type == 'O') {
                    process_output.push_back(work[working_on]);
                    sort(process_output.begin(), process_output.end(), compare);
                }
            } else {
                process_completed.push_back(work[working_on]);
            }
            round_robin_time = 0;
            work.erase(work.begin() + working_on);
            if (!work.empty()) {
                working_on %= work.size();
            } else {
                working_on = 0;
            }
        } else {
            round_robin_time++;
            if (round_robin_time == MAX_ROBIN) {
                round_robin_time = 0;
                working_on++;
                working_on %= work.size();
            }
        }
    }
}

#endif
#ifndef MLFQ_H
#define MLFQ_H
#include <unistd.h>
#include <algorithm>
#include <vector>
#include "print.h"
#include "structures.h"

void mlfq(vector<process> &work, vector<process> &process_completed,
          vector<process> &process_CPU, vector<process> &process_input,
          vector<process> &process_output, int &clk) {
    static int working_on = 0, index = 0;
    static int round_robin_time = 0;
    static int previous_custom_priority = 1;
    int current_custom_priority, count[3] = {0};
    vector<int> V[3];
    int MAX_ROBIN;
    static int reset = 0;

    for (int i = 0; i < work.size(); i++) {
        V[work[i].custom_priority - 1].push_back(i);
        count[work[i].custom_priority - 1]++;
        if(reset >= 100){
            work[i].custom_priority = 1;
        }
    }

    if(reset >= 100){
        reset = 0;
    }

    if (count[0] != 0) {
        current_custom_priority = 1;
        MAX_ROBIN = 1;
    } else if (count[1] != 0) {
        current_custom_priority = 2;
        MAX_ROBIN = 2;
    } else if (count[2] != 0) {
        current_custom_priority = 3;
        MAX_ROBIN = 3;
    }

    if (previous_custom_priority != current_custom_priority) {
        round_robin_time = 0;
        index = 0;
        if (current_custom_priority == 1) {
            working_on = V[0][0];
        } else if (current_custom_priority == 2) {
            working_on = V[1][0];
        } else if (current_custom_priority == 3) {
            working_on = V[2][0];
        }
    } else {
        working_on = V[current_custom_priority - 1][index];
    }

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
                if (working_on == work.size()) {
                    working_on = V[current_custom_priority - 1][0];
                    index = 0;
                }
            } else {
                working_on = 0;
                index = 0;
            }
        } else {
            round_robin_time++;
            if (round_robin_time == MAX_ROBIN) {
                round_robin_time = 0;
                index++;
                index %= V[current_custom_priority - 1].size();
                if (work[working_on].custom_priority < 3) {
                    work[working_on].custom_priority += 1;
                    // cout << "Move to Queue " <<
                    // work[working_on].custom_priority << endl;
                }
                working_on = V[current_custom_priority - 1][index];
            }
        }
    }
    previous_custom_priority = current_custom_priority;
    reset++;
}

#endif
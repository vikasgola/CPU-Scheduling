#ifndef LOTTERY_H
#define LOTTERY_H
#include <unistd.h>
#include <vector>
#include<algorithm>
#include<cstdlib>
#include "print.h"
#include "structures.h"

void lottery(vector<process> &work, vector<process> &process_completed,
          vector<process> &process_CPU, vector<process> &process_input,
          vector<process> &process_output, int &clk) {
    if (!work.empty()) {
        // work[0].mark = false;
        // table(process_CPU, process_input, process_output, process_completed, clk);

        int total_shares = 0;
        int lottery, curr_total_share = 0;
        if(&work == &process_CPU){
            for(int i=0;i<work.size();i++) total_shares += work[i].share;
            lottery = 1 + (rand() % total_shares);
            for(int i=0;i<work.size();i++){
                curr_total_share += work[i].share;
                if(curr_total_share >= lottery){
                    swap(work[0], work[i]);
                    break;
                }
            }
        }
        work[0].mark = true;
        table(process_CPU, process_input, process_output, process_completed, clk);
        work[0].mark = false;


        work[0].jobs[0].burst_time--;
        // table(process_CPU, process_input, process_output, process_completed, clk);
        if (work.size() > 1) {
            for (int i = 1; i < work.size(); i++) {
                work[i].waiting_time++;
            }
        }
        if (work[0].jobs[0].burst_time == 0) {
            process temp = work[0];
            work[0].jobs.erase(work[0].jobs.begin());
            work[0].arrival_time = clk;
            // work[0].mark = false;
            // table(process_CPU, process_input, process_output, process_completed, clk);


            if (!work[0].jobs.empty()) {
                if (work[0].jobs[0].type == 'C') {
                    process_CPU.push_back(work[0]);
                } else if (work[0].jobs[0].type == 'I') {
                    process_input.push_back(work[0]);
                    sort(process_input.begin(), process_input.end(), compare);
                } else if (work[0].jobs[0].type == 'O') {
                    process_output.push_back(work[0]);
                    sort(process_output.begin(), process_output.end(), compare);
                }
            }else{
                process_completed.push_back(work[0]); 
            }
            // table(process_CPU, process_input, process_output, process_completed, clk);
            work.erase(work.begin());
        }
        // table(process_CPU, process_input, process_output, process_completed, clk);
    }
}

#endif
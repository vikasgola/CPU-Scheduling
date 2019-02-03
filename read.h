#ifndef READ_H
#define READ_h

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
#include "structures.h"
using namespace std;

vector<process> readFile(string input_filename) {
    vector<process> process_list;
    ifstream input(input_filename);
    int n;
    string line;

    getline(input, line);
    stringstream words(line);
    words >> n;
    for (int i = 0; i < n; i++) {
        std::getline(input, line);
        stringstream words(line);
        job temp_job;
        string word;
        process temp_process;

        // making a string stream
        words >> temp_process.pid;
        words >> temp_process.arrival_time;
        words >> temp_process.priority;
        words >> temp_process.share;
        temp_process.mark = false;
        int flag = 0;
        // Read and print each word.
        while (words >> word) {
            if (word == "-1") {
                break;
            }
            if (flag == 0) {
                // cout << word << endl;
                temp_job.type = word[0];
                flag = 1;
            } else {
                temp_job.burst_time = stoi(word);
                temp_process.jobs.push_back(temp_job);
                flag = 0;
            }
        }
        process_list.push_back(temp_process);
    }
    sort(process_list.begin(), process_list.end(), compare);
    return process_list;
}

#endif
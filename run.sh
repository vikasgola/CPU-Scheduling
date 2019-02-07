#!/bin/bash

if [ "$1" = "-gt" ];
then
    python3 scripts/generate_testcases.py $2
else
    g++ -std=c++11 src/main.cpp -o bin/scheduling
    bin/scheduling $@
fi
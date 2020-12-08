//
//  main.cpp
//  AdventOfCode12-8-2020
//
//  Created by Melissa George on 12/8/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <regex>

using namespace std;

vector<pair<string, int>> bootcode;
void load_bootcode();
pair<bool, int> find_loop();
int fix_bootcode();

int main(int argc, const char * argv[])
{
    load_bootcode();
    
    pair<bool, int> part1 = find_loop();
    cout << "Part 1: accumulator value is: " << part1.second << endl;
    
    int part2 = fix_bootcode();
    cout << "Part 2: accumulator value is: " << part2 << endl;
}

void load_bootcode()
{
    ifstream infile("input.txt");
    string instruction;
    char operation;
    int value;
    
    while(infile >> instruction >> operation >> value)
    {
        if(operation == '-') value *= -1;
        bootcode.push_back(pair<string, int>(instruction, value));
    }
}

pair<bool, int> find_loop()
{
    unordered_map<int, bool> visited;
    int accumulator = 0;
    int current = 0;

    while(!visited[current] && current < bootcode.size())
    {
        visited[current] = true;
        
        if(bootcode[current].first == "jmp")
        {
            current += bootcode[current].second;
            continue;
        }
        
        if(bootcode[current].first == "acc")
            accumulator += bootcode[current].second;
        
        ++current;
    }
    
    if (current == bootcode.size())
        return pair<bool, int>(false, accumulator);
    else
        return pair<bool, int>(true, accumulator);
}

int fix_bootcode()
{
    pair<bool, int> result;
    
    for(size_t i = 0; i < bootcode.size(); ++i)
    {
        if(bootcode[i].first == "acc")
            continue;
        
        string& instruction = bootcode[i].first;
        instruction == "jmp"? instruction = "nop" : instruction = "jmp";
        result = find_loop();
        if (!result.first) break;
        instruction == "jmp"? instruction = "nop" : instruction = "jmp";
    }
    
    return result.second;
}

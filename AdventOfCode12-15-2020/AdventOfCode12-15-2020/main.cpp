//
//  main.cpp
//  AdventOfCode12-14-2020
//
//  Created by Melissa George on 12/14/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <bitset>
#include <math.h>
#include <map>
#include <unordered_map>

using namespace std;

vector<unsigned long> sequence;
void part1();
void part2();
void readinput();
unsigned long get_nth_num(unsigned long n);
vector<string> split(string s, string delimiter);

int main(int argc, const char * argv[])
{
    readinput();
    cout << "Part 1: " << get_nth_num(2020) << endl;
    cout << "Part 2: " << get_nth_num(30000000) << endl;
}

void readinput()
{
    ifstream infile("input.txt");
    string sequencestr;
    infile >> sequencestr;
    
    auto valstrs = split(sequencestr, ",");
    for(size_t i = 0; i < valstrs.size(); ++i)
        sequence.push_back(stoul(valstrs[i]));
}

unsigned long get_nth_num(unsigned long n)
{
    unsigned long value_idx = 0;
    unordered_map<unsigned long, unsigned long> last_seen;
    
    while(value_idx < sequence.size() - 1)
    {
        last_seen[sequence[value_idx]] = value_idx;
        value_idx++;
    }
    
    unsigned long current = sequence.back();
    unsigned long previous_val = current;
    
    while(value_idx < n)
    {
        previous_val = current;
        if(last_seen.find(previous_val) == last_seen.end())
            current = 0;
        else
            current = value_idx - last_seen[previous_val];

        last_seen[previous_val] = value_idx++;
    }

    return previous_val;
}

// Implementation for basic string split from day 4.
vector<string> split(string s, string delimiter)
{
    vector<string> parts;
    unsigned long start = 0;
    unsigned long position = s.find(delimiter, start);
    
    while (position != s.npos)
    {
        parts.push_back(s.substr(start, position - start));
        start = position + 1;
        position = s.find(delimiter, start);
    }
    
    parts.push_back(s.substr(start, position));
    
    return parts;
}

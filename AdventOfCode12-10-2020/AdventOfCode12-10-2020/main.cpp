//
//  main.cpp
//  AdventOfCode12-10-2020
//
//  Created by Melissa George on 12/10/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

vector<unsigned long long> values { 0 };

void part1();
void part2();

int main(int argc, const char * argv[])
{
    part1();
    part2();
}

void part1()
{
    ifstream infile("input.txt");
    unsigned long long highest = 0, temp;
    
    while(infile >> temp)
    {
        values.push_back(temp);
        highest = max(highest, temp);
    }
    
    values.push_back(highest + 3);
    
    int one_diffs = 0, three_diffs = 0;
    sort(values.begin(), values.end());
    
    for (size_t i = 1; i < values.size(); ++i)
    {
        one_diffs += values[i] - 1 == values[i - 1];
        three_diffs += values[i] - 3 == values[i - 1];
    }
    
    cout << "Part 1: " << one_diffs * three_diffs << endl;
    
    infile.close();
}

void part2()
{
    vector<unsigned long long> ways_to_reach_value;
    ways_to_reach_value.push_back(1);
    ways_to_reach_value.push_back(1);
    ways_to_reach_value.push_back(
      1 + 1 * (values[2] - values[0] < 3));
    
    for (size_t i = 3; i < values.size(); ++i)
    {
        unsigned long long ways_to_reach_current = 0;

        ways_to_reach_current += (values[i] - values[i-1] <= 3) * ways_to_reach_value[i-1];
        ways_to_reach_current += (values[i] - values[i-2] <= 3) * ways_to_reach_value[i-2];
        ways_to_reach_current += (values[i] - values[i-3] <= 3) * ways_to_reach_value[i-3];
        
        ways_to_reach_value.push_back(ways_to_reach_current);
    }
    
    cout << "Part 2: " << ways_to_reach_value.back() << endl;
}

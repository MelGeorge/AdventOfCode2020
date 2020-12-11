//
//  main.cpp
//  AdventOfCode12-9-2020
//
//  Created by Melissa George on 12/9/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

set<unsigned long long> window;
vector<unsigned long long> values;
unsigned long long find_invalid_number(int preamble_length);
unsigned long long find_encryption_weakness(unsigned long long invalid_num);

int main(int argc, const char * argv[])
{
    unsigned long long invalid = find_invalid_number(25);
    cout << "Part 1 invalid # is: " << invalid << endl;
    cout << "Part 2 encryption weakness: " << find_encryption_weakness(invalid) << endl;
}

unsigned long long find_invalid_number(int preamble_length)
{
    ifstream infile("input.txt");
    int nums = 0;
    unsigned long long temp;
    
    while(nums++ < preamble_length)
    {
        infile >> temp;
        window.insert(temp);
        values.push_back(temp);
    }
    
    int window_start = 0;
    int window_end = preamble_length;
    unsigned long long check_number;
    
    while(true)
    {
        bool valid = false;
        infile >> check_number;
        values.push_back(check_number);
        
        for (size_t i = window_start; i < window_end; ++i)
        {
            window.erase(values[i]);
            if (window.find(check_number - values[i]) != window.end())
            {
                valid = true;
                window.insert(values[i]);
                break;
            }
            window.insert(values[i]);
        }
        
        if (!valid)
            return check_number;
        
        window.erase(values[window_start++]);
        window.insert(values[window_end++]);
    }
}

unsigned long long find_encryption_weakness(unsigned long long invalid_num)
{
    int window_start = 0;
    int window_end = 0;
    
    unsigned long long sum = values[window_start];
    
    while (true)
    {
        if (sum < invalid_num)
            sum += values[++window_end];
        else if(sum > invalid_num)
            sum -= values[window_start++];
        else
        {
            unsigned long long max_value = *max_element(values.begin() + window_start, values.begin() + window_end + 1);
            unsigned long long min_value = *min_element(values.begin() + window_start, values.begin() + window_end + 1);
            return max_value + min_value;
        }
    }
}

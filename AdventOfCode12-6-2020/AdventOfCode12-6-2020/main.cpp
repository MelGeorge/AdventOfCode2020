//
//  main.cpp
//  AdventOfCode12-6-2020
//
//  Created by Melissa George on 12/6/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

void part1();
void part2();

int main(int argc, const char * argv[])
{
    part1();
    part2();
}

void part1()
{
    std::ifstream infile("input.txt");
    std::string line;
    std::set<char> questions;
    int sum = 0;
    
    while(std::getline(infile, line))
    {
        if(line.empty())
        {
            sum += questions.size();
            questions.clear();
        }
        
        for(char c : line)
            questions.insert(c);
    }
    
    sum += questions.size();
    
    std::cout << "Part 1 sum: " << sum << std::endl;
    infile.close();
}

void part2()
{
    std::ifstream infile("input.txt");
    std::string line;
    std::vector<int> questions(26, 0);
    int sum = 0;
    int group_size = 0;
    
    while (std::getline(infile, line))
    {
        if (line.empty())
        {
            for (int count : questions)
                sum += count == group_size;
        
            std::fill(questions.begin(), questions.end(), 0);
            group_size = 0;
        }
        else
        {
            group_size++;
            for (char c : line)
                questions[c - 'a']++;
        }
    }
    
    for (int count : questions)
        sum += count == group_size;
    
    std::cout << "Part 2 sum: " << sum << std::endl;
    infile.close();
}

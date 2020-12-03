//
//  main.cpp
//  AdventOfCode12-2-2020
//
//  Created by Melissa George on 12/2/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <fstream>

int part1();
int part2();

int main(int argc, const char * argv[]) {
    std::cout << "Valid passwords for part 1: " << part1() << std::endl;
    std::cout << "Valid passwords for part 2: " << part2() << std::endl;
}

int part1()
{
    std::ifstream infile("input.txt");
    std::unordered_map<int, bool> values;
    
    int min;
    int max;
    char crap;
    char letter;
    std::string password;
    int valid = 0;

    while(infile >> min >> crap >> max >> letter >> crap >> password)
    {
        int count = 0;
        for(int i = 0; i < password.length(); ++i)
        {
            if(password[i] == letter)
            {
                ++count;
            }
        }
        
        if(count >= min && count <= max)
        {
            valid++;
        }
    }
    
    return valid;
}

int part2()
{
    std::ifstream infile("input.txt");
    std::unordered_map<int, bool> values;
    
    int min;
    int max;
    char crap;
    char letter;
    std::string password;
    int valid = 0;
    
    while(infile >> min >> crap >> max >> letter >> crap >> password)
    {
        bool first = password[min - 1] == letter;
        bool second = password[max - 1] == letter;
        
        if(first xor second)
        {
            valid++;
        }
    }
    
    return valid;
}

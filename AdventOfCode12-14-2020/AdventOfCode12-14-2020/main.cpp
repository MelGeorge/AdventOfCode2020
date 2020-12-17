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

using namespace std;

struct Instruction
{
    Instruction(unsigned long address_in, unsigned long value_in) : address(address_in), value(value_in) {}
    unsigned long address;
    unsigned long value;
};

struct MaskSet
{
    MaskSet(string mask_in, vector<Instruction> instructions_in) : mask(mask_in), instructions(instructions_in) {}
    string mask;
    vector<Instruction> instructions;
};

void part1();
void part2();
void readinput();

map<unsigned long, unsigned long> memory;
vector<MaskSet> maskSets;

int main(int argc, const char * argv[])
{
    readinput();
    part1();
    part2();
}

void readinput()
{
    ifstream infile("input.txt");
    string str, mask, trash;
    unsigned long value;
    infile >> trash >> trash >> mask;
    
    vector<Instruction> instructions;
    
    while(infile >> str)
    {
        if(str == "mask")
        {
            MaskSet maskSet(mask, instructions);
            maskSets.push_back(maskSet);
            instructions.clear();
            infile >> trash >> mask;
        }
        else
        {
            unsigned long address = stoul(str.substr(str.find("[") + 1, str.find("]")));
            infile >> trash >> value;
            
            Instruction instruction(address, value);
            instructions.push_back(instruction);
        }
    }
    
    MaskSet maskSet(mask, instructions);
    maskSets.push_back(maskSet);
}

void part1()
{
    for(size_t i = 0; i < maskSets.size(); ++i)
    {
        MaskSet set = maskSets[i];
        for(size_t j = 0; j < set.instructions.size(); ++j)
        {
            unsigned long address = set.instructions[j].address;
            unsigned long value = set.instructions[j].value;
            
            string valstr = std::bitset<36>(value).to_string();
            
            for(size_t i = 0; i < set.mask.size(); ++i)
                valstr[i] = set.mask[i] == 'X' ? valstr[i] : set.mask[i];
            
            memory[address] = std::bitset<36>(valstr).to_ulong();
        }
    }

    unsigned long sum = 0;
    for(auto it = memory.begin(); it != memory.end(); ++it)
        sum += it->second;
    
    memory.clear();
    cout << "Part 1: " << sum << endl;
}

void part2()
{
    for(size_t i = 0; i < maskSets.size(); ++i)
    {
        MaskSet set = maskSets[i];
        for(size_t j = 0; j < set.instructions.size(); ++j)
        {
            unsigned long address = set.instructions[j].address;
            unsigned long value = set.instructions[j].value;
            string addrstr = std::bitset<36>(address).to_string();
            vector<string> addresses { addrstr };
            
            for(size_t i = 0; i < set.mask.size(); ++i)
            {
                if(set.mask[i] == 'X')
                {
                    vector<string> add;
                    for(size_t j = 0; j < addresses.size(); ++j)
                    {
                        addresses[j][i] = '0';
                        add.push_back(addresses[j]);
                        addresses[j][i] = '1';
                        add.push_back(addresses[j]);
                    }
                    addresses = add;
                }
                else if(set.mask[i] == '1')
                {
                    for(size_t j = 0; j < addresses.size(); ++j)
                    {
                        addresses[j][i] = '1';
                    }
                }
            }
            
            for(size_t i = 0; i < addresses.size(); ++i)
            {
                address = std::bitset<36>(addresses[i]).to_ulong();
                memory[address] = value;
            }
        }
    }
    
    unsigned long sum = 0;
    for(auto it = memory.begin(); it != memory.end(); ++it)
        sum += it->second;
    cout << "Part 2: " << sum << endl;
}

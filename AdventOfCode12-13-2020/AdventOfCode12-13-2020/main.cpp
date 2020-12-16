//
//  main.cpp
//  AdventOfCode12-12-2020
//
//  Created by Melissa George on 12/12/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

void readbuses(long long& starttime, vector<long long> & buses);
void part1(long long& starttime, vector<long long> & buses);
void part2(vector<long long>& buses);
std::vector<std::string> split(std::string s, std::string delimiter);
long long xGCD(long long a, long long b, long long &x, long long &y);
long long mod(long long val, long long modulus);

int main(int argc, const char * argv[])
{
    long long starttime;
    vector<long long> buses;
    
    readbuses(starttime, buses);
    part1(starttime, buses);
    part2(buses);
}

void readbuses(long long& starttime, vector<long long> & buses)
{
    ifstream infile("input.txt");
    infile >> starttime;
    string notes;
    infile >> notes;
    
    vector<string> busIDs = split(notes, ",");
    
    for(size_t i = 0; i < busIDs.size(); ++i)
    {
        try
        {
            long long bus = stoull(busIDs[i]);
            buses.push_back(bus);
        }
        catch (invalid_argument ex)
        {
            buses.push_back(0);
        }
    }
    
    infile.close();
}

void part1(long long& starttime, vector<long long>& buses)
{
    long long closesttime = LLONG_MAX;
    long long closestbus = LLONG_MAX;
    for(size_t i = 0; i < buses.size(); ++i)
    {
        if(buses[i] == 0 ) continue;
        long long time = (starttime / buses[i]) * buses[i];
        if(time < starttime) time += buses[i];
        
        if(time < closesttime)
        {
            closesttime = time;
            closestbus = buses[i];
        }
    }
    
    cout << "Part 1: " << (closesttime - starttime) * closestbus << endl;
}
// 399661675132684 too low lmao
// 7805491507337940 too high
void part2(vector<long long>& buses)
{
    long long n1 = buses[0];
    long long a1 = 0;
    
    set<long long> used;
    
    for(size_t i = 0; i < buses.size(); ++i)
    {
        if (buses[i] == 0) continue;
        long long temp = buses[i];
        cout << "i: " << i << " bus: " << temp << endl;
    }
    
    for(size_t i = 1; i < buses.size(); ++i)
    {
        if(buses[i] == 0) continue;
        
        long long n2 = buses[i];
        
        while(n2 < i)
        {
            n2 += buses[i]; // issue is that these aren't coprime
        }
        
        long long a2 = n2 - i;
        
        long long m1, m2;
        long long gcd = xGCD(n1, n2, m1, m2);
        a1 = (a1*m2*n2 + a2*m1*n1);
        a1 = mod(a1, (n1 * n2));
        n1 = n1 * n2;
    }
    
    for(size_t j = 0; j < buses.size(); ++j)
    {
        if(buses[j] == 0) continue;
        
        if ((a1 + j) % buses[j] != 0)
        {
            cout << "i : " << j << "bus: " << buses[j] << endl;
            cout << "expected: 0 actual: " <<(a1 + j) % buses[j] << endl;
        }
    }
    
    cout << "t is: " << a1 << endl;
}

// Implementation for basic string split from day 4.
std::vector<std::string> split(std::string s, std::string delimiter)
{
    std::vector<std::string> parts;
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

long long xGCD(long long a, long long b, long long &x, long long &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    long long x1, y1, gcd = xGCD(b, mod(a,b), x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

long long mod(long long val, long long modulus)
{
    while(val < 0) val += modulus;
    return val % modulus;
}

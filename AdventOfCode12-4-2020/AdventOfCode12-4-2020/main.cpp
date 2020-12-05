//
//  main.cpp
//  AdventOfCode12-4-2020
//
//  Created by Melissa George on 12/4/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

bool check_if_valid(std::unordered_map<std::string, std::string> fields);
std::vector<std::string> split(std::string s, std::string delimiter);
bool is_valid(std::string field_name, std::string field_value);
bool check_number(std::string num, size_t digits, int geq, int leq);

int main(int argc, const char * argv[]) {
    std::ifstream infile("input.txt");
    std::string line;
    std::unordered_map<std::string, std::string> fields;
    int valid = 0;

    while(std::getline(infile, line))
    {
        // If line is empty, evaluate the passport and clear fields.
        if(line.empty())
        {
            valid += check_if_valid(fields);
            fields.clear();
            continue;
        }
        
        // Split into key:value pairs and iterate.
        std::vector<std::string> vec = split(line, " ");
        for (std::string & str : vec)
        {
            std::vector<std::string> pair = split(str, ":");
            fields[pair[0]] = pair[1];
        }
    }
    
    // Last passport hasn't been evaluated.
    valid += check_if_valid(fields);
    
    std::cout << "# Valid Passports: " << valid << std::endl;
}

bool check_if_valid(std::unordered_map<std::string, std::string> fields)
{
    for(std::string needed : { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" })
    {
        //----- Part 1 and 2 need this check -----//
        if (fields.find(needed) == fields.end())
            return false;
        
        //----- Part 2 ONLY needs this check -----//
        if (!is_valid(needed, fields[needed]))
            return false;
    }
    
    return true;
}
           
bool is_valid(std::string field_name, std::string field_value)
{
    if (field_name == "byr")
    {
        return check_number(field_value, 4, 1920, 2002);
    }
    
    if (field_name == "iyr")
    {
        return check_number(field_value, 4, 2010, 2020);
    }
    
    if (field_name == "eyr")
    {
        return check_number(field_value, 4, 2020, 2030);
    }
    
    if (field_name == "hgt")
    {
        size_t is_cm = field_value.find("cm");
        size_t is_in = field_value.find("in");
        
        if (is_cm != field_value.npos)
        {
            std::string num = field_value.substr(0, is_cm);
            
            if (field_value.length() != num.length() + 2)
                return false;
            
            return check_number(num, 3, 150, 193);
        }
        else if (is_in != field_value.npos)
        {
            std::string num = field_value.substr(0, is_in);
            
            if (field_value.length() != num.length() + 2)
                return false;
            
            return check_number(num, 2, 59, 76);
        }
        
        return false;
    }
    
    if (field_name == "hcl")
    {
        if (field_value.length() != 7 || field_value[0] != '#')
            return false;
        
        for (size_t i = 1; i < field_value.length(); ++i)
        {
            char check = field_value[i];
            if (!(check >= '0' && check <= '9') && !(check >= 'a' && check <= 'f'))
                return false;
        }
    }
    
    if (field_name == "ecl")
    {
        std::vector<std::string> colors =
        { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
        
        for (std::string color : colors)
        {
            if (field_value == color)
                return true;
        }
        
        return false;
    }
    
    if (field_name == "pid")
    {
        return check_number(field_value, 9, 0, INT_MAX);
    }
    
    return true;
}

bool check_number(std::string num, size_t digits, int geq, int leq)
{
    if (num.length() != digits)
        return false;
    
    for (char digit : num)
    {
        if (digit > '9' || digit < '0')
            return false;
    }
    
    int result = stoi(num);
    return result >= geq && result <= leq;
}

// Implementation for basic string split; couldn't find one in the STL.
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

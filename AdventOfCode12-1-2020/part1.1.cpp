//
//  main.cpp
//  AdventOfCode12.1.2020
//
//  Created by Melissa George on 12/1/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <fstream>

int main(int argc, const char * argv[]) {
    std::ifstream infile("part1input");
    std::unordered_map<int, bool> values;
    
    int value;
    while(infile >> value)
    {
        if(values[2020 - value])
        {   
           std::cout << "Numbers are: " << 2020 - value << " and " << value << std::endl;
            std::cout << "Product is: " << (2020 - value) * value << std::endl;
            return 0;
        }
        else
        {
            values[value] = true;
        }
    }
    
    std::cout << "Result not found." << std::endl;
    return 0;
}


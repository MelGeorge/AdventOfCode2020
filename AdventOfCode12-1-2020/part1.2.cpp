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
#include <vector>

int main(int argc, const char * argv[]) {
    std::ifstream infile("part1input");
    std::unordered_map<int, std::pair<int, int> > sums;
    
    int value;
    std::vector<int> values;

    while(infile >> value)
    {
      values.push_back(value);
    }

    for(int i = 0; i < values.size(); ++i)
    {
       for(int j = i; j < values.size(); ++j)
       {
          if(i != j)
          {
             sums[values[i] + values[j]] = std::pair<int, int>(i, j);
          }
       }
    }

    for(int i = 0; i < values.size(); ++i)
    {
       int remainder = 2020 - values[i];
       if(sums.find(remainder) != sums.end()  && sums[remainder].first != i && sums[remainder].second != i)
       {
          int first = sums[remainder].first;
          int second = sums[remainder].second;
          std::cout << "Found result. Values: " << values[i] << ", " << values[first] << ", " << values[second] << std::endl;
          std::cout << "Product is: " << values[i] * values[first] * values[second] << std::endl;
       }
    }
    
    std::cout << "Result not found." << std::endl;
    return 0;
}


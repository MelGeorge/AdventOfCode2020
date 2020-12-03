//
//  main.cpp
//  AdventOfCode12-3-2020
//
//  Created by Melissa George on 12/3/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>

std::vector<std::string> forest;

void initialize_forest();
size_t get_num_trees(size_t right, size_t down);

int main(int argc, const char * argv[]) {
    // Initialize
    initialize_forest();
    
    // Calculate trees intersected for different slopes.
    size_t trees_1_1 = get_num_trees(1, 1); // Right 1, down 1.
    size_t trees_3_1 = get_num_trees(3, 1); // Right 3, down 1.
    size_t trees_5_1 = get_num_trees(5, 1); // Right 5, down 1.
    size_t trees_7_1 = get_num_trees(7, 1); // Right 7, down 1.
    size_t trees_1_2 = get_num_trees(1, 2); // Right 1, down 2.
    
    std::cout << "Part 1: " << trees_3_1 << std::endl;
    std::cout << "Part 2: " << trees_1_1 * trees_3_1 * trees_5_1 * trees_7_1 * trees_1_2 << std::endl;
}

void initialize_forest()
{
    std::ifstream infile("input.txt");
    std::string line;
    
    while(infile >> line)
    {
        forest.push_back(line);
    }
}

size_t get_num_trees(size_t right, size_t down)
{
    // Traverse map, count trees.
    size_t trees = 0;
    size_t row = 0;
    size_t col = 0;
    
    while(row < forest.size())
    {
        // Increment trees if this row/col has a tree.
        trees += forest[row][col] == '#';
        
        // Move 3 to the right and down 1.
        col = (col + right) % forest[row].size();
        row += down;
    }
    
    return trees;
}

//
//  main.cpp
//  AdventOfCode12-5-2020
//
//  Created by Melissa George on 12/5/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

const int row_digits = 7;
const int col_digits = 3;
int get_encoded_val(char * begin, char * end, char front_of_range, int max_val);

int main(int argc, const char * argv[]) {
    std::ifstream infile("input.txt");
    std::string line;
    
    std::vector<bool> seats(1000, false);
    int highest_seat = 0;
    
    while(infile >> line)
    {
        int row = get_encoded_val(&line[0], &line[row_digits], 'F', 127);
        int col = get_encoded_val(&line[row_digits], &line[row_digits + col_digits], 'L', 7);
        int seat_id = row * 8 + col;
        highest_seat = std::max(highest_seat, seat_id);
        
        seats[seat_id] = true;
    }
    
    size_t seat = 0;
    while(seats[seat] == 0) ++seat;
    while(seats[seat] != 0) ++seat;
    
    std::cout << "My seat # is: " << seat << std::endl;
    std::cout << "Highest seat ID: " << highest_seat << std::endl;
}

int get_encoded_val(char * begin, char * end, char front_of_range, int max_val)
{
    int min_val = 0;
    while(begin != end)
    {
        int half_range = (max_val - min_val)/2;
        *begin == front_of_range ? max_val = min_val + half_range : min_val = max_val - half_range;
        ++begin;
    }
    
    return min_val;
}

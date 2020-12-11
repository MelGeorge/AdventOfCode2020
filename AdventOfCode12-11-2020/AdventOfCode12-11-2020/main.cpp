//
//  main.cpp
//  AdventOfCode12-11-2020
//
//  Created by Melissa George on 12/11/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

struct point
{
public:
    
    point(int col_in, int row_in)
    {
        col = col_in;
        row = row_in;
    }
    
    int col, row;
};

vector<string> seats;
vector<string> original_seats;
void read_seats();
bool empty_seats(vector<point> (*visible_points)(int, int), int occupied_limit);
bool occupy_seats(vector<point> (*visible_points)(int, int));
void run_algorithm(vector<point> (*visibility_method)(int, int), int occupied_limit);
int find_num_occupied(int col, int row, vector<point> (*visible_points)(int, int));
vector<point> visible_points_1(int col, int row);
vector<point> visible_points_2(int col, int row);

int main(int argc, const char * argv[])
{
    read_seats();
    
    cout << "Part 1: " << endl;
    run_algorithm(&visible_points_1, 4);
    
    seats = original_seats;
    
    cout << "Part 2: " << endl;
    run_algorithm(&visible_points_2, 5);
}

void read_seats()
{
    ifstream infile("input.txt");
    string temp;
    while(infile >> temp)
        seats.push_back(temp);
    
    original_seats = seats;
    infile.close();
}

void run_algorithm(vector<point> (*visibility_method)(int, int), int occupied_limit)
{
    bool changed = true;
    bool occupy_step = true;
    
    while(changed)
    {
        if (occupy_step)
            changed = occupy_seats(visibility_method);
        else
            changed = empty_seats(visibility_method, occupied_limit);
        
        occupy_step = !occupy_step;
    }
    
    int num_occupied = 0;
    for(string row : seats)
        for(char col : row)
            if(col == '#')
                ++num_occupied;
    
    cout << "Num occupied seats: " << num_occupied << endl;
}

bool occupy_seats(vector<point> (*visible_points)(int, int))
{
    vector<string> new_seats = seats;
    bool changed = false;
    
    for(int col = 0; col < seats[0].length(); ++col)
    {
        for(int row = 0; row < seats.size(); ++row)
        {
            if(seats[row][col] != 'L')
                continue;
            
            if(find_num_occupied(col, row, visible_points) == 0)
            {
                new_seats[row][col] = '#';
                changed = true;
            }
        }
    }
    
    seats = new_seats;
    return changed;
}

bool empty_seats(vector<point> (*visible_points)(int, int), int occupied_limit)
{
    vector<string> new_seats = seats;
    bool changed = false;
    
    for(int col = 0; col < seats[0].length(); ++col)
    {
        for(int row = 0; row < seats.size(); ++row)
        {
            if(seats[row][col] != '#')
                continue;
            
            if(find_num_occupied(col, row, visible_points) >= occupied_limit)
            {
                new_seats[row][col] = 'L';
                changed = true;
            }
        }
    }
    
    seats = new_seats;
    return changed;
}

int find_num_occupied(int col, int row, vector<point> (*visible_points)(int, int))
{
    vector<point> check = (*visible_points)(col, row);
    
    int occupied = 0;
    
    for(point x : check)
    {
        if (x.col >= 0 && x.col <= seats[0].length()
            && x.row >= 0 && x.row <= seats.size()
            && seats[x.row][x.col] == '#')
            ++occupied;
    }
    
    return occupied;
}

vector<point> visible_points_1(int col, int row)
{
    point up(col, row - 1);
    point down(col, row + 1);
    point left(col - 1, row);
    point right(col + 1, row);
    point diag_LU(col - 1, row - 1);
    point diag_RU(col + 1, row - 1);
    point diag_LD(col - 1, row + 1);
    point diag_RD(col + 1, row + 1);
    
    vector<point> points
    {
        up,
        down,
        left,
        right,
        diag_LU,
        diag_RU,
        diag_LD,
        diag_RD
    };
    
    return points;
}

vector<point> visible_points_2(int col, int row)
{
    point up(col, row - 1);
    while(up.row > 0 && seats[up.row][up.col] == '.')
        --up.row;
    
    point down(col, row + 1);
    while(down.row < seats.size()
          && seats[down.row][down.col] == '.')
        ++down.row;
    
    point left(col - 1, row);
    while(left.col > 0 && seats[left.row][left.col] == '.')
        --left.col;
    
    point right(col + 1, row);
    while(right.col < seats[0].length()
          && seats[right.row][right.col] == '.')
        ++right.col;
    
    point diag_LU(col - 1, row - 1);
    while(diag_LU.col > 0 && diag_LU.row > 0
          && seats[diag_LU.row][diag_LU.col] == '.')
    {
        --diag_LU.col;
        --diag_LU.row;
    }
    
    point diag_RU(col + 1, row - 1);
    while(diag_RU.col < seats[0].length() && diag_RU.row > 0
          && seats[diag_RU.row][diag_RU.col] == '.')
    {
        ++diag_RU.col;
        --diag_RU.row;
    }
    
    point diag_LD(col - 1, row + 1);
    while(diag_LD.col < seats[0].length() && diag_LD.row > 0
          && seats[diag_LD.row][diag_LD.col] == '.')
    {
        --diag_LD.col;
        ++diag_LD.row;
    }
    
    point diag_RD(col + 1, row + 1);
    while(diag_RD.col < seats[0].length() && diag_RD.row > 0
          && seats[diag_RD.row][diag_RD.col] == '.')
    {
        ++diag_RD.col;
        ++diag_RD.row;
    }
    
    vector<point> points
    {
        up,
        down,
        left,
        right,
        diag_LU,
        diag_RU,
        diag_LD,
        diag_RD
    };
    
    return points;
}

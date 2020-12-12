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

# define PI 3.14159265358979323846

using namespace std;

struct point
{
    point(double x_in, double y_in) : x(x_in), y(y_in) {}
    double x;
    double y;
};

point part_1_point(0, 0);
double direction = 0; // degrees

point part_2_point(0, 0);
point waypoint(10, 1); // waypoint diff from ship

int main(int argc, const char * argv[])
{
    ifstream infile("input.txt");
    char instruction;
    double value;
    
    while(infile >> instruction >> value)
    {
        switch(instruction)
        {
            case 'N':
                part_1_point.y += value;
                waypoint.y += value;
                break;
            case 'S':
                part_1_point.y -= value;
                waypoint.y -= value;
                break;
            case 'E':
                part_1_point.x += value;
                waypoint.x += value;
                break;
            case 'W':
                part_1_point.x -= value;
                waypoint.x -= value;
                break;
            case 'F':
            {
                part_1_point.x += value * cos(direction*PI/180);
                part_1_point.y += value * sin(direction*PI/180);
                part_2_point.x += value * waypoint.x;
                part_2_point.y += value * waypoint.y;
                break;
            }
            case 'L':
            {
                direction += value;
                
                double theta = atan2(waypoint.y, waypoint.x) * 180 / PI + value;
                double radius = sqrt(waypoint.x*waypoint.x + waypoint.y*waypoint.y);
                
                waypoint.x = radius * cos(theta * PI/180);
                waypoint.y = radius * sin(theta * PI/180);
                
                break;
            }
            case 'R':
            {
                direction -= value;
                
                double theta = atan2(waypoint.y, waypoint.x) * 180 / PI - value;
                double radius = sqrt(waypoint.x*waypoint.x + waypoint.y*waypoint.y);
                
                waypoint.x = radius * cos(theta * PI/180);
                waypoint.y = radius * sin(theta * PI/180);
                
                break;
            }
            default:
                break;
        }
    }
    
    cout << "Part 1 Manhattan Distance: " << abs(part_1_point.x) + abs(part_1_point.y) << endl;
    cout << "Part 2 Manhattan Distance: " << abs(part_2_point.x) + abs(part_2_point.y) << endl;
}

//
//  main.cpp
//  AdventOfCode12-7-2020
//
//  Created by Melissa George on 12/7/20.
//  Copyright © 2020 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <regex>

using namespace std;

void build_maps();
int bags_inside(string bag);
void bags_outside(string bag, set<string>& top_level_bags);

// maps a color of bag to a list of bag colors that can contain it.
// ex: "light red bags contain 1 bright white bag, 2 muted yellow bags."
// bright white --> light red, muted yellow --> light red
map<string, vector<string>> bottom_up_mapping;

// maps a color of bag to a list of the bags and counts it contains.
// ex: "light red bags contain 1 bright white bag, 2 muted yellow bags."
// light red -> [{'bright white', 1}, {'muted yellow', 2}]
map<string, vector<pair<string, int> > > top_down_mapping;

int main(int argc, const char * argv[])
{
    build_maps();
    
    // Part 1
    set<string> top_level_bags;
    bags_outside("shiny gold", top_level_bags);
    cout << "The number of possible top-level bags containing a shiny gold bag: " << top_level_bags.size() << endl;
    
    // Part 2
    cout << "The number of bags inside a shiny gold bag: " << bags_inside("shiny gold") << endl;
}

void bags_outside(string bag, set<string>& top_level_bags)
{
    for(int i = 0; i < bottom_up_mapping[bag].size(); ++i)
    {
        string outer_bag = bottom_up_mapping[bag][i];
        top_level_bags.insert(outer_bag);
        bags_outside(outer_bag, top_level_bags);
    }
}

int bags_inside(string bag)
{
    vector<pair<string, int> >& bag_specs = top_down_mapping[bag];
    int num_bags_inside = 0;

    for(auto bag_spec : bag_specs)
        num_bags_inside += bag_spec.second + bags_inside(bag_spec.first) * bag_spec.second;
    
    return num_bags_inside;
}

void build_maps()
{
    ifstream infile("input.txt");
    string mystr;
    
    while(getline(infile, mystr))
    {
        regex container_regex("([a-z\\s+]+)( bags contain)(.*)");
        smatch container_matches;
        regex_match ( mystr.cbegin(), mystr.cend(), container_matches, container_regex);
        
        string top_level = container_matches[1];
        
        regex contained_regex("([0-9]+) ([a-z\\s+]+)( bag)");
        smatch contained_matches;
        regex_match ( mystr.cbegin(), mystr.cend(), contained_matches, contained_regex);
        
        int i = 1;
        while (regex_search(mystr, contained_matches, contained_regex)) {
            int num_bags = std::stoi(contained_matches[1]);
            string bag_type = contained_matches[2];
            pair<string, int> bag_spec(bag_type, num_bags);
            
            top_down_mapping[top_level].push_back(bag_spec);
            bottom_up_mapping[bag_type].push_back(top_level);
            
            mystr = contained_matches.suffix().str();
            i++;
        }
    }
    
    infile.close();
}

#ifndef NIKITA_UTILITIES_HPP
#define NIKITA_UTILITIES_HPP
#include <iostream>
#include "precomputation.hpp"
#include <math.h>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<vector<string>> read_file(string fname);

vector<vector<string>> read_file(string fname){
    vector<vector<string>> content;
    vector<string> row;
    string line, word;
    
    fstream file (fname, ios::in);
    if(file.is_open()) {
        while(getline(file, line))
        {
        row.clear();
        
        stringstream str(line);
        
        while(getline(str, word, ','))
        row.push_back(word);
        content.push_back(row);
        }
    }
    else { cout<<"Could not open the file\n"; }
    return content;
}

#endif
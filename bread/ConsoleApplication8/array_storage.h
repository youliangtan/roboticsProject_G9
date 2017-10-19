#ifndef ARRAY_STORAGE_H_INCLUDED
#define ARRAY_STORAGE_H_INCLUDED

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
template <typename T>
int store(char* filename, vector< vector<T> > vect)
{
    ofstream file;
    file.open(filename);
    if(!file.is_open())
    {
        return -1;
    }
    typename vector< vector<T> >::iterator row;
    typename vector<T>::iterator column;
    for(row = vect.begin(); row != vect.end(); row++)
    {
        for(column = row->begin(); column != row->end(); column++)
        {
            file <<  *column;
            if((column + 1) != row->end()) file << ',';
        }
        if((row + 1) != vect.end())file << '\n';
    }
        file.close();
        return 0;
}

template <typename T>
int read(char* filename, vector< vector<T> > &vect)
{
    vect.clear();
    string cell, line;
    ifstream file;
    file.open(filename);
    if(!file.is_open())
    {
        return -1;
    }
    while(file.good())
    {
        getline(file, line);
        stringstream row(line);
        vector<T> row_vect;
        while(row.good())
        {
            getline(row, cell, ',');
            stringstream ss(cell);
            T val;
            ss >> val;
            row_vect.push_back(val);
        }
        vect.push_back(row_vect);
    }

    return 0;
}

#endif // ARRAY_STORAGE_H_INCLUDED
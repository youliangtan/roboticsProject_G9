#include "array_storage.h"
#include <iostream>

int main()
{
    char* filename = "test.csv";
    /*
    int row = 0, column = 0, counter = 0;
    printf("Enter rows: ");
    scanf("%d", &row);
    printf("Enter columns: ");
    scanf("%d", &column);
    vector< vector<int> > vect(row, vector<int>(column));
    for(int i = 0; i < row; i++)
        for(int j = 0; j < column; j++)
        {
            vect[i][j] = counter;
            counter++;
        }
    if(store(filename, vect) == -1)printf("Failed");
    */
    vector< vector<int> > vect2;
    read(filename, vect2);

    for(auto i = vect2.begin(); i != vect2.end(); i++)
    {
        for(auto j = i->begin(); j != i->end(); j++) std::cout << *j << '\t';
        std::cout << endl;
    }

    return 0;
}


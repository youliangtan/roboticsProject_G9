#include "roboticfunc.h"

using namespace std;

int func(mode Mode,int number)
{
    string filename;
    vector< vector<int> > vect;
    switch(Mode)
    {
    case egg: filename = "egg.csv"; break;
    case bread: filename = "bread.csv"; break;
    case drinks: filename = "drinks.csv"; break;
    }

    store(filename.c_str(), vect); //Load vector

    //Iterator
    for(auto it = vect.begin(); it != vect.end(); it++)
    {
        for(auto it2 = it->begin(); it2 != it2->end(); it2++)
        {
            static counter = 1;
            dxl_write_word(counter, /*MOVE*/, *it2);
        }
        Sleep(1000);
    }
    //Iterator

    /*write_to_UI();*/

    return 0;
}

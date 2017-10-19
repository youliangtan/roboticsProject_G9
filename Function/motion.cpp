#include "motion.h"

using namespace std;

int arm_motion(mode Mode,int pick_pos, int tray_pos)
{
    int pos;
    string pick_filename,tray_filename;
    vector< vector<int> > vect;
    switch(Mode)
    {
    case bread: pick_filename = "bread" + pick_pos + ".csv"; tray_filename = "bread_tray" + tray_pos + ".csv"; break;
    case egg: pick_filename = "egg.csv"; tray_filename = "egg_tray" + tray_pos + ".csv"; break;
    case drinks: pick_filename = "drinks.csv"; break;
    }


    //1st cycle: Initial position -> pickup -> intermediate position
    read(filename.c_str(), vect); //Load vector
    //Iterator
    for(auto it = vect.begin(); it != vect.end(); it++)
    {
        for(auto it2 = it->begin(); it2 != it2->end(); it2++)
        {
            static counter = 1;
            dxl_write_word(counter, /*MOVE*/, *it2);
        }
        while(/* TODO: waiting to reach final position*/)
    }

    //2nd cycle: intermediate position -> tray position -> initial position
    read(tray_filename.c_str(), vect); //Load vector
    //Iterator
    for(auto it = vect.begin(); it != vect.end(); it++)
    {
        for(auto it2 = it->begin(); it2 != it2->end(); it2++)
        {
            static counter = 1;
            dxl_write_word(counter, /*MOVE*/, *it2);
        }
        while(/* TODO: waiting to reach final position*/)
    }

    return 0;
}

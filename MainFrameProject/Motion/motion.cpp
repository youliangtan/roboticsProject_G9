#include "motion.h"
#define NO_OF_MOTORS 6

using namespace std;

int arm_motion(mode Mode,int pick_pos, int tray_pos)
{
    int pick_pos, tray_pos;
    string pick_filename,tray_filename;
    vector< vector<int> > vect;
    switch(Mode)
    {
    case bread: pick_filename = "bread_pick" + pick_pos + ".csv"; tray_filename = "bread_tray" + tray_pos + ".csv"; break;
    case egg: pick_filename = "egg_pick.csv"; tray_filename = "egg_tray" + tray_pos + ".csv"; break;
    case drinks: pick_filename = "drinks.csv"; break;
    }


    //1st cycle: Initial position -> pickup -> intermediate position
    read(filename.c_str(), vect); //Load vector
    //Iterator
    for(auto it = vect.begin(); it != vect.end(); it++)
    {
        for(int counter = 1; counter <= NO_OF_MOTORS; counter++)
        {
            int time = it[NO_OF_MOTORS + 1]; //Time is stored in the column after the last motor
            int theta = abs(it[counter] - dxl_read_word(counter, CUR_POS));
            int velocity = theta/time;
            dxl_write_word(counter, MOV_VEL, velocity);
            dxl_write_word(counter, END_POS, it[counter]);
        }
        while(/* TODO: waiting to reach final position*/)
    }

    Sleep(1000);

    //2nd cycle: intermediate position -> tray position -> initial position
    read(tray_filename.c_str(), vect); //Load vector
    //Iterator
    for(auto it = vect.begin(); it != vect.end(); it++)
    {
        for(int counter = 1; counter <= NO_OF_MOTORS; counter++)
        {
            int time = it[NO_OF_MOTORS + 1]; //Time is stored in the column after the last motor
            int theta = abs(it[counter] - dxl_read_word(counter, CUR_POS));
            int velocity = theta/time;
            dxl_write_word(counter, MOV_VEL, velocity);
            dxl_write_word(counter, END_POS, it[counter]);
        }
        while(/* TODO: waiting to reach final position*/)
    }

    return 0;
}

#ifndef MOTION_H_INCLUDED
#define MOTION_H_INCLUDED

#include <string>
#include <windows.h>
#include "array_storage.h"

enum mode {egg, bread, drinks};

int arm_motion(mode, int pick_pos, int tray_pos);


#endif // ROBOTICFUNC_H_INCLUDED

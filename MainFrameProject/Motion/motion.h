#ifndef MOTION_H_INCLUDED
#define MOTION_H_INCLUDED

#include <string>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "array_storage.h"
#include "dynamixel.h"

#pragma comment(lib, "dynamixel.lib")

#define TORQUE_SWITCH	24
#define END_POS			30
#define MOV_VEL			32
#define CUR_POS			36
#define MOVING			46

#define PORTNUM			5
#define BAUDNUM			1

#define JOINT_1			1
#define JOINT_2			2
#define JOINT_3			3
#define JOINT_4			4
#define GRIPPER_LEFT	5
#define GRIPPER_RIGHT	6

#define MAX_VEL			90	//To set the max angular velocity

enum mode {egg, bread, drinks};

int arm_motion(mode, int pick_pos, int tray_pos);


#endif // ROBOTICFUNC_H_INCLUDED

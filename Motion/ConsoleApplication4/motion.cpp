#include "stdafx.h"
#include "motion.h"
#define NO_OF_MOTORS 6

int previous[6] = {0};
using namespace std;
void init() {
	if (dxl_initialize(PORTNUM, BAUDNUM) == 0) {
		printf("Failed to connect to Robotic Arm...\n\n");
		printf("Press 'Esc' to terminate or any other key to retry...\n");
		if (_getch() == 0x1b) {
			dxl_terminate();
			exit(0);
		}
		else
			init();
	}
		else {
		lock_joints();
		vector< vector<int> > vect;
		if (!read("init.csv", vect))exit(0);
		for (int counter = 0; counter < NO_OF_MOTORS; counter++)
		{
			dxl_write_word(counter + 1, TORQUE_LIMIT, 800);
			dxl_write_word(counter + 1, MOV_VEL, MAX_VEL);
			dxl_write_word(counter + 1, END_POS, vect[0][counter]);
			printf("%d	%d	%d\n", counter + 1, TORQUE_LIMIT, 800);
			printf("%d	%d	%d\n", counter + 1, MOV_VEL, MAX_VEL);
			printf("%d	%d	%d\n", counter + 1, END_POS, vect[0][counter]);
		}

		printf("Successfully connected to Robotic Arm.");
		for (int i = 0; i < 3; i++) {
			printf(".");
			Sleep(500);
		}
		printf("\n");
	}
}

int arm_motion(mode Mode, int pick_pos, int tray_pos)
{
	stringstream pick_filename, tray_filename;
	vector< vector<int> > vect;
	switch (Mode)
	{
	case bread: pick_filename << "bread_pick" << pick_pos << ".csv"; tray_filename << "bread_tray.csv"; break;
	case egg: pick_filename << "egg_pick.csv"; tray_filename << "egg_tray" << tray_pos << ".csv"; break;
	case drinks: pick_filename << "drinks.csv"; break;
	}

	printf("%s\n", pick_filename.str().c_str());
	//1st cycle: Initial position -> pickup -> intermediate position
	if (!read(pick_filename.str().c_str(), vect))exit(0); //Load vector
														  //Iterator
	for (auto it = vect.begin(); it != vect.end(); it++) //Loop through all time-step
	{
		for (int counter = 0; counter < NO_OF_MOTORS; counter++)
		{
			int time_millis = (*it)[NO_OF_MOTORS]; //Time is stored in the column after the last motor
			float theta = fabs((*it)[counter] - dxl_read_word(counter + 1, CUR_POS))*(300.0 / 1023.0);
			/*
			float theta = fabs((*it)[counter] - previous[counter])*(300.0 / 1023.0);
			*/
			int rpm = (theta / (time_millis / 1000.0))*(60.0 / 360.0)*(1023.0 / 114.0);
			if (rpm == 0)rpm = 1;

			dxl_write_word(counter + 1, MOV_VEL, rpm);
			dxl_write_word(counter + 1, END_POS, (*it)[counter]);

			printf("%d	%d	%d\n", counter + 1, MOV_VEL, rpm);
			printf("%d	%d	%d\n", counter + 1, END_POS, (*it)[counter]);
			/*
			previous[counter] = (*it)[counter];
			*/
		}
		Sleep((*it)[NO_OF_MOTORS]);
		while (is_moving());
	}

	if (Mode == drinks)exit(0);
	printf("%s\n", tray_filename.str().c_str());

	//2nd cycle: intermediate position -> tray position -> initial position
	if (!read(tray_filename.str().c_str(), vect))exit(0); //Load vector
														  //Iterator
	for (auto it = vect.begin(); it != vect.end(); it++)
	{
		for (int counter = 0; counter < NO_OF_MOTORS; counter++)
		{
			int time_millis = (*it)[NO_OF_MOTORS]; //Time is stored in the column after the last motor
		
			float theta = fabs((*it)[counter] - dxl_read_word(counter + 1, CUR_POS))*(300.0 / 1023.0);
			/*
			float theta = fabs((*it)[counter] - previous[counter])*(300.0 / 1023.0);
			*/
			int rpm = (theta / (time_millis / 1000.0))*(60.0 / 360.0)*(1023.0 / 114.0);
			if (rpm == 0)rpm = 1;
			else if (rpm >= 1023)rpm = 1023;
			
			dxl_write_word(counter + 1, MOV_VEL, rpm);
			dxl_write_word(counter + 1, END_POS, (*it)[counter]);
			printf("%d	%d	%d\n", counter + 1, MOV_VEL, rpm);
			printf("%d	%d	%d\n", counter + 1, END_POS, (*it)[counter]);
			/*
			previous[counter] = (*it)[counter];
			*/

		}
		Sleep((*it)[NO_OF_MOTORS]);
		while (is_moving());
	}
	return 0;
}

void unlock_joints() {
	dxl_write_word(JOINT_1, TORQUE_SWITCH, 0);
	dxl_write_word(JOINT_2, TORQUE_SWITCH, 0);
	dxl_write_word(JOINT_3, TORQUE_SWITCH, 0);
	dxl_write_word(JOINT_4, TORQUE_SWITCH, 0);
	printf("UNLOCK \n");
}

void lock_joints() {
	dxl_write_word(JOINT_1, TORQUE_SWITCH, 1);
	dxl_write_word(JOINT_2, TORQUE_SWITCH, 1);
	dxl_write_word(JOINT_3, TORQUE_SWITCH, 1);
	dxl_write_word(JOINT_4, TORQUE_SWITCH, 1);
	printf("LOCK \n");
}

bool is_moving()
{
	for (int counter = 1; counter <= NO_OF_MOTORS; counter++)
	{
		if (dxl_read_word(counter, MOVING))return true;   //Check if any motor is moving.
		printf("%d	%d\n", counter, MOVING);
	}
	return false;                                       //If none are moving, false is returned.
}

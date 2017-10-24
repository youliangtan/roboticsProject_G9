#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "dynamixel.h"

#pragma comment(lib, "dynamixel.lib")

#define TORQUE_SWITCH	24
#define END_POS			30
#define MOV_VEL			32
#define TORQUE_LIMIT	34
#define CUR_POS			36
#define MOVING			46

#define PORTNUM			3
#define BAUDNUM			1

#define JOINT_1			1
#define JOINT_2			2
#define JOINT_3			3
#define JOINT_4			4
#define GRIPPER_LEFT	5
#define GRIPPER_RIGHT	6

#define MAX_VEL			90	//To set the max angular velocity

int main() {

	dxl_initialize(PORTNUM, BAUDNUM);
	
	dxl_write_word(JOINT_1, 6, 0);
	dxl_write_word(JOINT_1, 7, 1023);
	dxl_write_word(JOINT_2, 6, 200);
	dxl_write_word(JOINT_2, 7, 823);
	dxl_write_word(JOINT_3, 6, 0);
	dxl_write_word(JOINT_3, 7, 1023);
	dxl_write_word(JOINT_4, 6, 0);
	dxl_write_word(JOINT_4, 7, 1023);
	
	dxl_write_word(JOINT_1, TORQUE_LIMIT, 800);
	dxl_write_word(JOINT_2, TORQUE_LIMIT, 600);
	dxl_write_word(JOINT_3, TORQUE_LIMIT, 800);
	dxl_write_word(JOINT_4, TORQUE_LIMIT, 800);
	dxl_write_word(GRIPPER_LEFT, TORQUE_LIMIT, 800);
	dxl_write_word(GRIPPER_RIGHT, TORQUE_LIMIT, 800);

	dxl_write_word(JOINT_1, MOV_VEL, MAX_VEL);
	dxl_write_word(JOINT_2, MOV_VEL, MAX_VEL);
	dxl_write_word(JOINT_3, MOV_VEL, MAX_VEL);
	dxl_write_word(JOINT_4, MOV_VEL, MAX_VEL);
	dxl_write_word(GRIPPER_LEFT, MOV_VEL, MAX_VEL);
	dxl_write_word(GRIPPER_RIGHT, MOV_VEL, MAX_VEL);

	int JOINT_1_POS = 300;
	int JOINT_2_POS = 400;
	int JOINT_3_POS = 300;
	int JOINT_4_POS = 400;
	int GRIPPER_LEFT_POS = 512;
	int GRIPPER_RIGHT_POS = 512;

	dxl_write_word(JOINT_1, END_POS, JOINT_1_POS);
	dxl_write_word(JOINT_2, END_POS, JOINT_2_POS);
	dxl_write_word(JOINT_3, END_POS, JOINT_3_POS);
	dxl_write_word(JOINT_4, END_POS, JOINT_4_POS);
	dxl_write_word(GRIPPER_LEFT, END_POS, GRIPPER_LEFT_POS);
	dxl_write_word(GRIPPER_RIGHT, END_POS, GRIPPER_RIGHT_POS);
	
	printf("\n=======================MOVE=======================\n");
	while (1) {	
		char input = _getch();
		switch (input) {
		case 'q':
			JOINT_1_POS -= 10;
			dxl_write_word(JOINT_1, END_POS, JOINT_1_POS);
			break;
		case 't':
			JOINT_1_POS += 10;
			dxl_write_word(JOINT_1, END_POS, JOINT_1_POS);
			break;
		case 'w':
			JOINT_2_POS -= 10;
			dxl_write_word(JOINT_2, END_POS, JOINT_2_POS);
			break;
		case 's':
			JOINT_2_POS += 10;
			dxl_write_word(JOINT_2, END_POS, JOINT_2_POS);
			break;
		case 'e':
			JOINT_3_POS -= 10;
			dxl_write_word(JOINT_3, END_POS, JOINT_3_POS);
			break;
		case 'd':
			JOINT_3_POS += 10;
			dxl_write_word(JOINT_3, END_POS, JOINT_3_POS);
			break;
		case 'r':
			JOINT_4_POS -= 10;
			dxl_write_word(JOINT_4, END_POS, JOINT_4_POS);
			break;
		case 'f':
			JOINT_4_POS += 10;
			dxl_write_word(JOINT_4, END_POS, JOINT_4_POS);
			break;
		case 'a':
			dxl_write_word(GRIPPER_LEFT, END_POS, GRIPPER_LEFT_POS -= 20);
			dxl_write_word(GRIPPER_RIGHT, END_POS, GRIPPER_RIGHT_POS += 20);
			break;
		case 'g':
			dxl_write_word(GRIPPER_LEFT, END_POS, GRIPPER_LEFT_POS += 20);
			dxl_write_word(GRIPPER_RIGHT, END_POS, GRIPPER_RIGHT_POS -= 20);
			break;
		}
	}
}
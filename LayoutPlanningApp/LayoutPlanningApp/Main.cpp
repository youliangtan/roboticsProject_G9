#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
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

//Change the values here to record the values for future tests... Otherwise it will be reinstantiated to 0...
int JOINT_1_POS[9] = { 512,200,500,600,200,600,750,521,521 };
int JOINT_2_POS[9] = { 512,300,400,600,200,300,250,234,235 };
int JOINT_3_POS[9] = { 512,400,300,600,200,300,750,453,554 };
int JOINT_4_POS[9] = { 512,500,200,600,200,600,250,444,444 };
int GRIPPER_LEFT_POS = 512;
int GRIPPER_RIGHT_POS = 513;

void init();
void select_system_mode();
void calibrate_positions();
void move_mode();
void unlock_joints();
void lock_joints();
int get_largest(int *arr, int size);

int main() {
	init();
	while (1) {
		select_system_mode();
	}
}

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
		dxl_write_word(JOINT_1, 34, 800);
		dxl_write_word(JOINT_2, 34, 800);
		dxl_write_word(JOINT_3, 34, 800);
		dxl_write_word(JOINT_4, 34, 800);
		dxl_write_word(GRIPPER_LEFT, 34, 800);
		dxl_write_word(GRIPPER_RIGHT, 34, 800);

		dxl_write_word(JOINT_1, MOV_VEL, MAX_VEL);
		dxl_write_word(JOINT_2, MOV_VEL, MAX_VEL);
		dxl_write_word(JOINT_3, MOV_VEL, MAX_VEL);
		dxl_write_word(JOINT_4, MOV_VEL, MAX_VEL);
		dxl_write_word(GRIPPER_LEFT, MOV_VEL, MAX_VEL);
		dxl_write_word(GRIPPER_RIGHT, MOV_VEL, MAX_VEL);

		dxl_write_word(JOINT_1, END_POS, 512);
		dxl_write_word(JOINT_2, END_POS, 666);
		dxl_write_word(JOINT_3, END_POS, 205);
		dxl_write_word(JOINT_4, END_POS, 666);
		dxl_write_word(GRIPPER_LEFT, END_POS, 512);
		dxl_write_word(GRIPPER_RIGHT, END_POS, 513);

		printf("Successfully connected to Robotic Arm.");
		for (int i = 0; i < 3; i++) {
			printf(".");
			Sleep(500);
		}
	}
}

void select_system_mode() {
	system("CLS");
	printf("  Please select the mode you would like to run in:\n");
	printf("	1. Calibrate Positions\n");
	printf("	2. Move Mode\n");
	printf("	Esc Key. System Shutdown\n");

	switch (_getch()) {
	case '1':
		calibrate_positions();
		break;
	case '2':
		move_mode();
		break;
	case 0x1b:
		dxl_terminate();
		exit(0);
	default:
		printf("\nInvalid Input.\n");
		Sleep(500);
	}
}

void calibrate_positions() {
	boolean return_to_main = false;
	while (return_to_main == false) {
		system("CLS");
		printf("==========POSITION CALIBRATION MODE==========\n");
		printf("Please select the positions you would like to configure\n");
		printf("	1. Position 1\n");
		printf("	2. Position 2\n");
		printf("	3. Position 3\n");
		printf("	4. Position 4\n");
		printf("	5. Position 5\n");
		printf("	6. Position 6\n");
		printf("	7. Position 7\n");
		printf("	8. Position 8\n");
		printf("	9. Position 9\n");
		printf("	p. Print current angular positions of previous joint configuration\n");
		printf("	Esc Key. Return to Mode Selection Screen\n\n");
		char input = _getch();
		int i = (int)(input - '1');
		char yn;
		switch (input) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			unlock_joints();
			printf("Please move arm to the desired orientation for Position[%d] and then press 'y'...\n", i+1);
			printf("Otherwise press any other key to exit...\n");
			yn = _getch();
			if (yn == 'y') {
				JOINT_1_POS[i] = dxl_read_word(JOINT_1, CUR_POS);
				JOINT_2_POS[i] = dxl_read_word(JOINT_2, CUR_POS);
				JOINT_3_POS[i] = dxl_read_word(JOINT_3, CUR_POS);
				JOINT_4_POS[i] = dxl_read_word(JOINT_4, CUR_POS);
				printf("Position[%d] has been updated.\n", i+1);
				Sleep(100);
				printf(".");
				Sleep(100);
				printf(".");
				Sleep(100);
				printf(".");
			}
			else {
				printf("Exited without saving.\n");
				Sleep(500);
			}
			lock_joints();
			break;

		case 'p':
			printf("The current angular positions are:\n");
			printf("	Joint 1: %d\n", dxl_read_word(JOINT_1, CUR_POS));
			printf("	Joint 2: %d\n", dxl_read_word(JOINT_2, CUR_POS));
			printf("	Joint 3: %d\n", dxl_read_word(JOINT_3, CUR_POS));
			printf("	Joint 4: %d\n\n", dxl_read_word(JOINT_4, CUR_POS));
			printf("Press any key to return to previous screen.\n");
			_getch();
			break;

		case 0x1b:
			return_to_main = true;
			break;
		default:
			printf("\nInvalid Input.\n");
			Sleep(500);
		}
	}
}

void move_mode() {
	boolean return_to_main = false;
	while (return_to_main == false) {
		system("CLS");
		printf("==========MOVE MODE==========\n");
		printf("Please select the positions you would like to move to\n");
		printf("	1. Move to Position 1\n");
		printf("	2. Move to Position 2\n");
		printf("	3. Move to Position 3\n");
		printf("	4. Move to Position 4\n");
		printf("	5. Move to Position 5\n");
		printf("	6. Move to Position 6\n");
		printf("	7. Move to Position 7\n");
		printf("	8. Move to Position 8\n");
		printf("	9. Move to Position 9\n");
		printf("	q. Open Gripper\n");
		printf("	w. Close Gripper\n");
		printf("	Esc Key. Return to Mode Selection Screen\n\n");
		char input = _getch();
		int i = (int)(input - '1');
		int MOV_VEL_1;
		int MOV_VEL_2;
		int MOV_VEL_3;
		int MOV_VEL_4;
		int theta_1;
		int theta_2;
		int theta_3;
		int theta_4;
		int arr[4];
		int largest_theta;

		switch (input) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			theta_1 = abs(JOINT_1_POS[i] - dxl_read_word(JOINT_1, CUR_POS));
			theta_2 = abs(JOINT_2_POS[i] - dxl_read_word(JOINT_2, CUR_POS));
			theta_3 = abs(JOINT_3_POS[i] - dxl_read_word(JOINT_3, CUR_POS));
			theta_4 = abs(JOINT_4_POS[i] - dxl_read_word(JOINT_4, CUR_POS));
			arr[0] = theta_1 == 0 ? 1 : theta_1;
			arr[1] = theta_2 == 0 ? 1 : theta_2;
			arr[2] = theta_3 == 0 ? 1 : theta_3;
			arr[3] = theta_4 == 0 ? 1 : theta_4;
			largest_theta = get_largest(arr, 4);

			MOV_VEL_1 = (double)MAX_VEL / largest_theta * theta_1;
			MOV_VEL_2 = (double)MAX_VEL / largest_theta * theta_2;
			MOV_VEL_3 = (double)MAX_VEL / largest_theta * theta_3;
			MOV_VEL_4 = (double)MAX_VEL / largest_theta * theta_4;

			dxl_write_word(JOINT_1, MOV_VEL, MOV_VEL_1);
			dxl_write_word(JOINT_2, MOV_VEL, MOV_VEL_2);
			dxl_write_word(JOINT_3, MOV_VEL, MOV_VEL_3);
			dxl_write_word(JOINT_4, MOV_VEL, MOV_VEL_4);

			dxl_write_word(JOINT_1, END_POS, JOINT_1_POS[i]);
			dxl_write_word(JOINT_2, END_POS, JOINT_2_POS[i]);
			dxl_write_word(JOINT_3, END_POS, JOINT_3_POS[i]);
			dxl_write_word(JOINT_4, END_POS, JOINT_4_POS[i]);

			while ((dxl_read_word(JOINT_1, MOVING)||dxl_read_word(JOINT_2, MOVING)||dxl_read_word(JOINT_3, MOVING)||dxl_read_word(JOINT_4, MOVING))==1);
			printf("Arm has moved to Position[%d].", i+1);
			Sleep(100);
			printf(".");
			Sleep(100);
			printf(".");
			Sleep(100);
			printf(".\n");
			break;
		case 'q':
			dxl_write_word(GRIPPER_LEFT, END_POS, GRIPPER_LEFT_POS-=20);
			dxl_write_word(GRIPPER_RIGHT, END_POS, GRIPPER_RIGHT_POS += 20);
			break;
		case 'w':
			dxl_write_word(GRIPPER_LEFT, END_POS, GRIPPER_LEFT_POS += 20);
			dxl_write_word(GRIPPER_RIGHT, END_POS, GRIPPER_RIGHT_POS -= 20); v 
			break;
		case 0x1b:
			return_to_main = true;
			break;
		default:
			printf("\nInvalid Input.\n");
			Sleep(500);
		}
	}
}

void unlock_joints() {
	dxl_write_word(JOINT_1, TORQUE_SWITCH, 0);
	dxl_write_word(JOINT_2, TORQUE_SWITCH, 0);
	dxl_write_word(JOINT_3, TORQUE_SWITCH, 0);
	dxl_write_word(JOINT_4, TORQUE_SWITCH, 0);
}

void lock_joints() {
	dxl_write_word(JOINT_1, TORQUE_SWITCH, 1);
	dxl_write_word(JOINT_2, TORQUE_SWITCH, 1);
	dxl_write_word(JOINT_3, TORQUE_SWITCH, 1);
	dxl_write_word(JOINT_4, TORQUE_SWITCH, 1);
}

int get_largest(int *arr, int size) {
	int largest = 0;
	for (int i = 0; i < size; i++) {
		if (largest < *arr) {
			largest = *arr;
		}
		arr++;
	}
	return largest;
}
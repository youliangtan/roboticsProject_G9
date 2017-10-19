/*#include <windows.h>
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
#define GRIPPER_6		6

#define MAX_VEL			90

//Change the values here to record the values for future tests... Otherwise it will be reinstantiated to 0... between 175 - 798
int JOINT_1_POS[9] = { 512,200,500,600,200,600,750,521,521 };
int JOINT_2_POS[9] = { 512,300,400,600,200,300,250,234,235 };
int JOINT_3_POS[9] = { 512,400,300,600,200,300,750,453,554 };
int JOINT_4_POS[9] = { 512,500,200,600,200,600,250,444,444 };

int CommStatus;

void init();
void unlock_joints();
void lock_joints();
int get_largest(int *arr, int size);
void PrintErrorCode();
void PrintCommStatus(int CommStatus);

int main() {
	init();

	for (int i = 0;i < 10;i++) {

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
		/*
		theta_1 = abs(JOINT_1_POS[i] - dxl_read_word(JOINT_1, CUR_POS));
		theta_2 = abs(JOINT_2_POS[i] - dxl_read_word(JOINT_2, CUR_POS));
		theta_3 = abs(JOINT_3_POS[i] - dxl_read_word(JOINT_3, CUR_POS));
		theta_4 = abs(JOINT_4_POS[i] - dxl_read_word(JOINT_4, CUR_POS));
		arr[0] = theta_1 == 0 ? 1 : theta_1;
		arr[1] = theta_2 == 0 ? 1 : theta_2;
		arr[2] = theta_3 == 0 ? 1 : theta_3;
		arr[3] = theta_4 == 0 ? 1 : theta_4;
		largest_theta = get_largest(arr, 4);

		MOV_VEL_1 = (int)round((double)MAX_VEL / largest_theta * theta_1);
		MOV_VEL_2 = (int)round((double)MAX_VEL / largest_theta * theta_2);
		MOV_VEL_3 = (int)round((double)MAX_VEL / largest_theta * theta_3);
		MOV_VEL_4 = (int)round((double)MAX_VEL / largest_theta * theta_4);

		dxl_write_word(JOINT_1, MOV_VEL, MOV_VEL_1);
		dxl_write_word(JOINT_2, MOV_VEL, MOV_VEL_2);
		dxl_write_word(JOINT_3, MOV_VEL, MOV_VEL_3);
		dxl_write_word(JOINT_4, MOV_VEL, MOV_VEL_4);
		
		if (dxl_get_result() != COMM_RXSUCCESS)
		{
			printf("Error after MOV_VEL write\n");
			PrintErrorCode();
			PrintCommStatus(CommStatus);
		}

		//dxl_write_word(JOINT_1, END_POS, JOINT_1_POS[i]);
		dxl_write_word(JOINT_2, END_POS, JOINT_2_POS[i]);
		//dxl_write_word(JOINT_3, END_POS, JOINT_3_POS[i]);
		//dxl_write_word(JOINT_4, END_POS, JOINT_4_POS[i]);
		if (dxl_get_result() != COMM_RXSUCCESS)
		{
			printf("Error after GOAL_POS write\n");
			PrintErrorCode();
			PrintCommStatus(CommStatus);
		}
		Sleep(5000);
	}
}

void init() {
	if (dxl_initialize(PORTNUM, BAUDNUM) == 0) {
		printf("Failed to connect to Robotic Arm...\n\n");
		printf("Press 'Esc' to terminate or any other key to retry...\n");
		if (_getch() == 0x1b) {
			dxl_terminate();
			exit(1);
		}
		else
			init();
	}
	else {
		//dxl_write_word(JOINT_1, MOV_VEL, MAX_VEL);
		dxl_write_word(JOINT_2, MOV_VEL, MAX_VEL);
		//dxl_write_word(JOINT_3, MOV_VEL, MAX_VEL);
		//dxl_write_word(JOINT_4, MOV_VEL, MAX_VEL);

		//dxl_write_word(JOINT_1, END_POS, 512);
		dxl_write_word(JOINT_2, END_POS, 666);
		//dxl_write_word(JOINT_3, END_POS, 205);
		//dxl_write_word(JOINT_4, END_POS, 666);

		//while ((dxl_read_word(JOINT_1, MOVING)||dxl_read_word(JOINT_2, MOVING)||dxl_read_word(JOINT_3, MOVING)||dxl_read_word(JOINT_4, MOVING)) == 1);
		printf("Successfully connected to Robotic Arm.");
		for (int i = 0; i < 3; i++) {
			printf(".");
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

void PrintCommStatus(int CommStatus)
{
	switch (CommStatus)
	{
	case COMM_TXFAIL:
		printf("COMM_TXFAIL: Failed transmit instruction packet!\n");
		break;

	case COMM_TXERROR:
		printf("COMM_TXERROR: Incorrect instruction packet!\n");
		break;

	case COMM_RXFAIL:
		printf("COMM_RXFAIL: Failed get status packet from device!\n");
		break;

	case COMM_RXWAITING:
		printf("COMM_RXWAITING: Now recieving status packet!\n");
		break;

	case COMM_RXTIMEOUT:
		printf("COMM_RXTIMEOUT: There is no status packet!\n");
		break;

	case COMM_RXCORRUPT:
		printf("COMM_RXCORRUPT: Incorrect status packet!\n");
		break;

	default:
		printf("This is unknown error code!\n");
		break;
	}
}

// Print error bit of status packet
void PrintErrorCode()
{
	if (dxl_get_rxpacket_error(ERRBIT_VOLTAGE) == 1)
		printf("Input voltage error!\n");

	if (dxl_get_rxpacket_error(ERRBIT_ANGLE) == 1)
		printf("Angle limit error!\n");

	if (dxl_get_rxpacket_error(ERRBIT_OVERHEAT) == 1)
		printf("Overheat error!\n");

	if (dxl_get_rxpacket_error(ERRBIT_RANGE) == 1)
		printf("Out of range error!\n");

	if (dxl_get_rxpacket_error(ERRBIT_CHECKSUM) == 1)
		printf("Checksum error!\n");

	if (dxl_get_rxpacket_error(ERRBIT_OVERLOAD) == 1)
		printf("Overload error!\n");

	if (dxl_get_rxpacket_error(ERRBIT_INSTRUCTION) == 1)
		printf("Instruction code error!\n");
}*/
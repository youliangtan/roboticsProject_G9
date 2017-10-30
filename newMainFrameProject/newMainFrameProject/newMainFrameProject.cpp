// newMainFrameProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "motion.h"
#include "ArdSensor.h"
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<string.h>
#include<iostream>
#include<string>
#include <windows.h>
#include <stdlib.h>
#include <sstream>
#include "dynamixel.h"

#pragma comment(lib, "dynamixel.lib")
using namespace std;

char ChoiceFilePath[] = "../UI_display/static/choice.txt";
char StatusFilePath[] = "../UI_display/static/status.txt";



struct choicelist 
{
	char drink;
	char a, b;
	int numbread;
	char d;
	
	int numegg;
	
}choice;



int writeUI(string status) {
	//write status command to status.txt
	ofstream myfile;
	myfile.open(StatusFilePath);
	myfile << status;
	myfile.close();
	return 0;
}

int ultraRead( ArdSensor* ard1, int N, int numbread)
{
	
	int startPos;
	/*Read ultrasonic reading of bread*/

	// if cumalative value of bread smaller than 4, sensor1 being called to scan 1st raw
	
	
		int distance = ard1->ardRead("U");
		
		if (distance > 4 && distance <= 14)
		{
			startPos = 1;
			return startPos;
		}
		else if (distance > 4 && distance <= 19)
		{
			startPos = 2;
			return startPos;
		}
		else if(distance > 4 &&  distance <= 25)
		{
			startPos = 3;
			return startPos;
		}

		else
		{
			startPos = 4;
			return startPos;
		}

	/*	else
		{
			/*ask ultrasonic sensor scan the distance again
			startPos = ultraRead(ArdSensor* ard1, N, numbread);
			return startPos;
		}*/

	

	//if cumlative value smaller than 7 but bigger than 3, 2nd sensor is called to scan 2nd raw.
	/*else if (N<7)
	{
		//int distance = ard1->ardRead("U2");
		
		if (distance<10)
		{
			startPos = 1;
			return startPos;
		}
		else if (distance < 20)
		{
			startPos = 2;
			return startPos;
		}
		else if (distance < 30)
		{
			startPos = 3;
			return startPos;
		}

		else
		{
			/*ask ultrasonic sensor scan the distance again*/
/*			startPos = ultraRead(position, N, numbread);
			return startPos;
		}

	}*/


	//once cumaltive value of N exceed 6, N will be initialised to 0 again
/*	else 
	{
		N = 0;
		N += numbread;
		return ultraRead(position, N, numbread);
	} */

	

}

void clear_struct()
{
	choice.drink = NULL;
	choice.a = NULL;
	choice.b = NULL;
	choice.numbread = NULL;
	choice.d = NULL;
	choice.numegg = NULL;
}



int main() {
	//read selection from choice.txt
	//return array address of selection
	int N = 0;
	int Position;
	int quit = 3;
	int dyna_port;
	int ard_port;
	
	
	printf("Arduino Port:");
	scanf_s("%d", &ard_port);
	printf("Dynamixel Port:");
	scanf_s("%d", &dyna_port);
	//read selection from choice.txt
	//return array address of selection
	ArdSensor ard1(ard_port);
	if (!ard1.exist())
	{
		printf("Exiting.\n");
		exit(0);
	}
	init(dyna_port);
	while (true)
	{
		ifstream myfile(ChoiceFilePath);
		if (myfile.is_open())
		{

			myfile >> choice.drink >> choice.a >> choice.numbread >> choice.b >> choice.numegg >> choice.d;
		

			if (choice.d == NULL)
			{
				//wait until user input the string and UI send the string to txt file
				printf("file is not ready.\n");
				Sleep(1000);
			}
			else if (choice.d =='.')
			{
				printf("Preparing Meal.\n");
				Sleep(1000);
				//delete contents of myfile.
				myfile.close();
				//perform actions..
				char Drink = choice.drink;
				if (Drink == 'C')
				{
					printf("coffee ordered by user\n");
				}
				else
				{
					printf("tea ordered by user\n");
				}
				int numBread = choice.numbread;
				printf("%d bread ordered by user\n", numBread);
				int numEgg = choice.numegg;
				printf("%d egg ordered by user\n", numEgg);

				//cumalative value of bread
				N += numBread;



				/*for bread*/
				int i;
				int startPos;

				for (i = 1; i <= numBread; i++)
				{
					while (true)
					{
						static int success = 0, fail = 0 ;
						int value = ard1.ardRead("U");
						std::cout << value << std::endl;
						if (value <= 200 && value >= 5)
						{
							success++;
							fail = 0;
						}
						else
						{
							success = 0;
							fail++;
							std::cout << "Reset" << std::endl;
						}

						std::cout << "Success counter:" << success << std::endl;
						std::cout << "Fail counter: " << fail << std::endl;

						if (success > 2 || fail > 2) 
						{
							success = 0;
							fail = 0;
							break;
						}
					}
					startPos = ultraRead(&ard1, N, numBread);
					printf("Performing number %d motion of bread.\n", i);
					writeUI("toast");
					
					arm_motion(bread_pick, startPos);
					arm_motion(bread_tray, 0);
					printf("number %d motion of bread is done.\n", i);

				}

				/*for egg*/
				for (i = 1; i <= numEgg; i++)
				{
					writeUI("eggs");

					printf("Performing number %d motion of egg.\n", i);
					arm_motion(egg_pick, 0);
					arm_motion(egg_tray, i);
					printf("%dst motion of egg is performed.\n", i);

				}

				/*for drinks*/
				writeUI("drinks");
				arm_motion(drinks_pick, 0);
				/*Arduino water dispenser*/
				int delay = ard1.ardRead("D");
				if(delay)
				{
					Sleep(delay);
					std::cout << "Delay " << delay << "ms" << std::endl;
				}
				else
				{
					Sleep(2000);
					std::cout << "Delay 2000ms" << std::endl;
				}
				arm_motion(drinks_tray, 0);

				//finish and ready to serve!!
				writeUI("finish");
				printf("finish.\n");
				clear_struct();
				myfile.close();
				Sleep(10000);

			}
			
		}



		else
		{
			cout << "Unable to open file";
			
		}
	}
	return 0;
}

		
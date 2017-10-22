#include"stdafx.h"
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<string>
#include<iostream>

using namespace std;

#define PORT_NUM 6
string readUI();
char ChoiceFilePath[] = "../UI_display/static/choice.txt";
char StatusFilePath[] = "../UI_display/static/status.txt";


int writeUI(string status){
	//write status command to status.txt
	ofstream myfile;
	myfile.open (StatusFilePath);
	myfile << status;
	myfile.close();
	return 0;
}

string readUI(){
	//read selection from choice.txt
	//return array address of selection
	string line;
	ifstream myfile (ChoiceFilePath);
	if (myfile.is_open())
	{
	  while ( getline (myfile,line) )
	  {
		cout << choice << '\n';
	  }
	  myfile.close();
	}
	else cout << "Unable to open file";
	return 0;
}

int ultraRead(ArdSensor* ard1,int N,int numbread)
{	
	/*Read ultrasonic reading of bread*/
	
	// if cumalative value of bread smaller than 4, sensor1 being called to scan 1st raw
	if (N < 4) 
	{
		int distance = ard1->ardRead("U1");
		if (0 < distance < 10)
		{
			startPos = 1;
			return startPos;
		}
		else if (10 < distance < 20)
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
			startPos = ultraRead(ard1);
			return startPos;
		}

	}

	//if cumlative value smaller than 7 but bigger than 3, 2nd sensor is called to scan 2nd raw.
	else if (N<7)
	{
		int distance1 = ard1->ardRead("U2");
		if (0 < distance1 < 10)
		{
			startPos = 1;
			return startPos;
		}
		else if (10 < distance2 < 20)
		{
			startPos = 2;
			return startPos;
		}
		else if (distance3 < 30)
		{
			startPos = 3;
			return startPos;
		}

		else
		{
			/*ask ultrasonic sensor scan the distance again*/
			startPos = ultraRead(ard1);
			return startPos;
		}

	}


	//once cumaltive value of N exceed 6, N will be initialised to 0 again
	else
	{
		N = 0;
		N += numbread;
		return ultraRead(ard1, N, numbread);
	}
	
}

int main()
{
	//cumalative number of bread
	int N = 0;

	//character
	char ch;

	//we will input any character to start the process
	printf("Input any character to start the process.\n");
	printf("type q to terminate the process.\n");
	scanf("%c", ch);

	while (ch != q)
	{
		/*user input number of bread,number of cup,tea or coffee*/
		/*Read a txt file */
		string choice = readUI();

		//choice is in "c,1,0" or "t,2,2" format
		char drink = choice[0];
		int numBread = atoi(choice[2].c_str());
		int numEgg = atoi(choice[4].c_str());

		/*Initialize Arduino*/
		ArdSensor* ard1(PORT_NUM);

		//cumalative value of bread
		N += numBread;

		/*for bread*/
		for (i = 1; i < numBread; i++)
		{
			startPos = ultraRead(ard1,N,numBread);
			writeUI("Bread");
			arm_motion(Bread, startPos, NULL);

		}

		/*for egg*/
		for (i = 1; i < numEgg; i++)
		{
			writeUI("Egg");
			arm_motion(Egg, NULL, i + 1);

		}

		/*for drinks*/
		writeUI("Drink");
		arm_motion(Drink, NULL, NULL);

		//finish and ready to serve!!
		writeUI("finish");

		//press q to terminate the process
		printf("If you wish to quit the process,press q.\n");
		scanf("%c", ch);
	}
}

#include "stdafx.h"
#include<stdio.h>
#include<fstream>
#include<iostream>

namespace std;

int main()
{
	/*user input number of bread,number of cup,tea or coffee*/
	/*Read a txt file */

	ifstream fp;
	fp.open("Choice.txt");

	if{

	}






	/*for bread*/
	for (i = 1; i < numBread; i++)
	{
		startPos = ultraRead();
		writeUI("Bread");
		funcm("Bread", startPos, NULL);

	}

	/*for egg*/
	for (i = 1; i < numEgg; i++)
	{
		writeUI("Egg");
		funcm("Egg", NULL, i + 1);

	}

	/*for drinks*/
	writeUI("Drink");
	funcm("Drink", NULL, NULL);



	/*Read ultrasonic reading of bread*/
	ultraRead()
	{
		distance = ard1.ardRead(U);

		if (0 < distance < 10)
		{
			startPos = 1;
		}

		else if (10 < distance < 20)
		{
			startPos = 2;
		}

		else if (distance < 30)
		{
			startPos = 3;
		}

		else if (distance < 40)
		{
			startPos = 4;
		}

		else if (distance < 50)
		{
			startPos = 5;
		}

		else
		{
			/*ask ultrasonic sensor scan the distance again*/
			startPos = ultraRead();
		}
	}
}

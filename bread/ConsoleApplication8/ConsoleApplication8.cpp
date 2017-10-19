// ConsoleApplication8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "array_storage.h"
#include <stdio.h>
/*#include "dynamixel.h"*/
#include <conio.h>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;
/*#pragma comment(lib,"dynamixel.lib")

#define END_POS       30
#define MOV_VEL       32
#define TORQUE_LIMIT  34
#define PORTNUM       3
#define BAUDNUM       1*/


/*bread function*/
int main()
{
    /*Read arrays from a txt file  */

	ifstream fin;
	fin.open("bread.txt");
	int n1;      /*n means number of intermediate position*/
	int n2;
	int j;
	int k;
	int A[20][5]; /*A matrix consist n rows and n column*/
	int B[20][5];
	if (fin.fail())
	{
		cerr << "Error Opening File";
	}

   /*Only read 1st line of matrix A*/

	for (n2 = 0; n2 < 6; n2++)
	{
		fin >> A[0][n2];
	}

	/*Move to intial position*/

	/*
	 for(i=0;i<=5;i++)
	 {
	   dxl_write_word(i+1,B[0][i],A[0][i]);

	  } */


	/*Rest for 10ms*/
	/*sleep(10);*/

	/*Move to nth intermediate position and rest*/
	int n3;
	printf("how many intermediate position required?");
	scanf("%d", &n3);
	/*if the intermediate position exceed 19,ask user to input until less than 19*/

        while(n3>19)
		{
			prinf("please reenter the number of intermediate required");
			scanf("%d", &n3);
		}


		/* Move
		for (n1 = 1; n1 <= n3; n1++)
		{

			for(i=0;i<=5;i++)
			{
			  dxl_write_word(i+1,B[n1][i],A[n1][i];

			}

			sleep(10);
		}*/

	/*After the loop is over, matrix B will pointed to B[n3+1][0] and A will pointed to A[n3+1][0]*/

	/*Move to tray position

	  Maximum step=20
	  Remaining step:20-1-n3=19-n3

	  for(i=0;i<=5;i++)
	  {
	     dxl_write_word(i+1,B[n3+1][i],A[n3+1][i];

	   }
	   Remaining step:18-n3

	/*Move to nth intermediate position and rest*/

		int n4;
		printf("how many intermediate position required?");
		scanf("%d", &n4);

		while (n4 > 18 - n3)
		{
			printf("Please reenter again ");
			scanf("%d", &n4);
		}


		for (j=n3+2; j <= n3+n4+2; j++)
	   {
		/*move*/
			for (i = 0; i <= 5; i++)
			{
				dxl_write_word(i + 1, B[j][i], A[j][i]);
			}
		/*rest*/
			sleep(100);
	    }

	/*Move to intial position*/

		for (i = 0; i <= 5; i++)
		{
			dxl_write_word(i + 1, B[j + 1][i], A[0][i]);
		}











	return 0;
}


//============================================================================
// Name        : ArdSensor.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */
#include <string.h>
#include <iostream>
#include "arduSensor.h"

int main()
{
	char portName[20],func[20], output[30];
	int ERROR;
	printf("Enter portname: ");	
	scanf("%s", portName);
	arduSensor sensor(portName);			//Initialize by entering portname (eg. /dev/ttyUSB0)
	while(true)
	{
		memset(func, 0, sizeof(func));		
		printf("Input function: ");
		scanf("%s", func);		
		if(strcmp(func,"quit") == 0)break;
		printf("%d\n",sensor.ardRead(func));	//sensor.ardRead("<command>"), returns arduino values in int 
	}
	return 0;
}

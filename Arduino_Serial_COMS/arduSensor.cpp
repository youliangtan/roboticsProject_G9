#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "arduSensor.h"

using namespace std;

arduSensor::arduSensor(const char* portName)
{
    struct termios tty;
    fd = open(portName,O_RDWR | O_NOCTTY| O_NDELAY);
    if(fd == -1)
    {
    	printf("Failed to open %s.\n", portName);
    	error = -1;
	throw -1;
    }
    else
    {
    	printf("%s openned succesfully.\n", portName);
    	error = 0;
    }
    tcgetattr(fd, &tty);
    /* Set Baud Rate */
    cfsetospeed (&tty, (speed_t)B9600);
    cfsetispeed (&tty, (speed_t)B9600);


    cfmakeraw(&tty);
    /* Setting other Port Stuff */
    tty.c_cflag     &=  ~PARENB;            // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

    tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    tty.c_cc[VMIN]   =  1;                  // read blocks
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
    tcsetattr(fd,TCSANOW, &tty);
    sleep(1);
}

int arduSensor::ardRead(const char* mode)
{
	char data[256] = {0}; 	
	writeData(mode);
	sleep(1);
	if(readData(data))return atoi(data);
	else return -1; 
}

int arduSensor::writeData(const char* dataOut)
{

	printf("%s\n", dataOut);
	int  bytes_written  =  0;
	bytes_written = write(fd,dataOut,sizeof(dataOut) - 1);
	return bytes_written;

}

int arduSensor::readData(char* dataIn)
{
	char temp;
	int counter = 0;
	int bytes_read = 0;
	do
	{		
		bytes_read = read(fd, &temp, sizeof(temp));
		if(bytes_read > 0)
		{
			dataIn[counter] = temp;
			counter += bytes_read;
		}
	}while(bytes_read > 0);
	return counter;
}

arduSensor::~arduSensor()
{
    close(fd);
}



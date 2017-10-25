
#include "stdafx.h"
#include "ArdSensor.h"
#include <sstream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
//#include "dynamixel.h"

//#pragma comment(lib, "dynamixel.lib")
using namespace std;

ArdSensor::ArdSensor(int portNum)
{
    stringstream ss;
    string port = "\\\\.\\COM";
    ss << portNum;
    port += ss.str();

    hComm = CreateFile((LPCWSTR)port.c_str(),          // for COM1—COM9 only
                       GENERIC_READ | GENERIC_WRITE, //Read/Write
                       0,               // No Sharing
                       NULL,            // No Security
                       OPEN_EXISTING,   // Open existing port only
                       0,               // Non Overlapped I/O
                       NULL);
    if (hComm == INVALID_HANDLE_VALUE)printf("Error in opening serial port.\n");
    else printf("Opening serial port successful.\n");

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hComm, &dcbSerialParams);

    dcbSerialParams.BaudRate = CBR_9600;  // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;// Setting StopBits = 1
    dcbSerialParams.Parity   = NOPARITY;  // Setting Parity = None
    SetCommState(hComm, &dcbSerialParams);

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout         = 50; // in milliseconds
    timeouts.ReadTotalTimeoutConstant    = 50; // in milliseconds
    timeouts.ReadTotalTimeoutMultiplier  = 10; // in milliseconds
    timeouts.WriteTotalTimeoutConstant   = 50; // in milliseconds
    timeouts.WriteTotalTimeoutMultiplier = 10; // in milliseconds
    SetCommTimeouts(hComm, &timeouts);
    Sleep(1000);
}

int ArdSensor::ardRead(const char* command)
{
    char data[256] = {};

    if(this->writeData(command))
    {
        Sleep(1000);
        this->readData(data);
        return atoi(data);
    }
    else return -1;
}

bool ArdSensor::writeData(const char* dataOut)
{
    DWORD dNoOFBytestoWrite;         // No of bytes to write into the port
    DWORD dNoOfBytesWritten;     // No of bytes written to the port
    dNoOFBytestoWrite = strlen(dataOut);
    int Status = 0;
    Status = WriteFile(hComm,        // Handle to the Serial port
                       dataOut,     // Data to be written to the port
                       dNoOFBytestoWrite,  //No of bytes to write
                       &dNoOfBytesWritten, //Bytes written
                       NULL);
    if(Status)
    {
        return true;
    }
    else
    {
        return false;
    }

}

int ArdSensor::readData(char* dataIn)
{
    char TempChar; //Temporary character used for reading
    DWORD NoBytesRead;
    int i = 0;

    do
    {

        ReadFile(hComm,           //Handle of the Serial port
                &TempChar,       //Temporary character
                sizeof(TempChar),//Size of TempChar
                &NoBytesRead,    //Number of bytes read
                NULL);
        if(NoBytesRead != 0)
        {
            dataIn[i] = TempChar;// Store Tempchar into buffer
            i++;
        }
    }
    while (NoBytesRead > 0);
    return (i - 1);
}

ArdSensor::~ArdSensor()
{
    CloseHandle(hComm);
}

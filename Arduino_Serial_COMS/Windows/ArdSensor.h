#ifndef ARDSENSOR_H
#define ARDSENSOR_H
#include <windows.h>
#include <stdio.h>
#include <string>


class ArdSensor
{
    public:
        ArdSensor(int portNum);
        virtual ~ArdSensor();
        char outgoingData[256];
        char incomingData[256];
        int ardRead(const char* command);
        bool writeData(const char* dataOut);
        int readData(char* dataIn);

    protected:

    private:
        HANDLE hComm;

};

#endif // ARDSENSOR_H

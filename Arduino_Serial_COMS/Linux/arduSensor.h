#ifndef ARDUSENSOR_H
#define ARDUSENSOR_H
#include <stdio.h>

using namespace std;

class arduSensor
{
    public:
        arduSensor(const char* portName);
        virtual ~arduSensor();
        char outgoingData[256];
        char incomingData[256];
	int writeData(const char* dataOut);
        int readData(char* dataIn);
        int ardRead(const char* mode);

    protected:

    private:
        int fd;
	int error;

};

#endif

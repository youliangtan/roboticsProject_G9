#include <stdio.h>
#include "ArdSensor.h"
#include <windows.h>
int main()
{
    int port_num;
    char input[256] = "";
    char output[256] = "";
    printf("Input port number: ");
    scanf("%d", &port_num);
    ArdSensor ard1(port_num);
    while(true)
    {
        printf("Type input:");
        scanf("%s", input);
        ard1.writeData(input);
        Sleep(100);
        ard1.readData(output);
        printf(output);
    }

    return 0;
}

#include <stdio.h>
#include <string>
#include <iostream>
#include "ArdSensor.h"

using namespace std;

int main()
{
    int port_num;
    cout<< "Input port number: ";
    scanf("%d", &port_num);
    ArdSensor ard1(port_num); //enter the port_num in COM<port_num>
    char command[20] = {0};
    while(true)
    {
        memset(command, 0, sizeof(command));
        printf("Enter command: ");
        scanf("%s", command);
        if(strcmp(command,"quit") == 0)break;
        cout<<"Reading " << command << ":" << ard1.ardRead(command) <<endl;
        cout<<endl;
    }
    return 0;
}


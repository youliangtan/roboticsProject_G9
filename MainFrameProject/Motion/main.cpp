#include "motion.h"

int main(){
init();
char s[10];
bool loop;
do{
arm_motion(bread, 1, 1);
/*
arm_motion(egg, 0, 1);
arm_motion(drinks, 0, 0);
*/
printf("Loop? (y/n)\n");
scanf("%s", s);
if(strcmp(s,"y") == 0)loop = true;
else loop = false;
}while(loop);
}

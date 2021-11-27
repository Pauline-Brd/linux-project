#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RED1 14
#define RED2 13

#define YELLOW1 12
#define YELLOW2 3

#define GREEN1 0
#define GREEN2 7

int main(int argc, char **argv[]) {

        int x=0;
        int LedPin=atoi(argv[1]);

        if(strcmp("RED1",argv[1])==0)
                LedPin=RED1;
        if(strcmp("RED2",argv[1])==0)
                LedPin=RED2;

        if(strcmp("YELLOW1",argv[1])==0)
                LedPin=YELLOW1;
        if(strcmp("YELLOW2",argv[1])==0)
                LedPin=YELLOW2;

        if(strcmp("GREEN1",argv[1])==0)
                LedPin=GREEN1;
        if(strcmp("GREEN2",argv[1])==0)
                LedPin=GREEN2;

        if(wiringPiSetup() == -1) { //when initialize wiringPi failed, print$
                printf("setup wiringPi failed !\n");
                return -1;
        }

        pinMode(LedPin, OUTPUT);
        sleep(1);
        digitalWrite(LedPin, LOW);  //led Off
        return 0;
}

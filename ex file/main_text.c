#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

#include "lcd.h"
void sig_handler(int sig);

int main(void){
	//printf("HELLO World");
	signal(SIGINT, sig_handler);
	if(wiringPiSetupGpio() ==-1) {
		fprintf(stdout, "Unable to start wiringpi GPIO: %s\n", strerror(errno));
		return 1;
	}
	
	delay(50);
	initLcd();
	delay(50);
	printString("HELLO World!!!");
	setDDRAMAddress();
	move2ndLine();
	printString("Raspberry Pi!!!");
	while(1)
	{
		
	}
	return 0;
	
}

void sig_handler(int sig)
{
	initLcd();
	exit(0);
}

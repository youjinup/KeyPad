#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

#include "pir.h"
#include "lcd.h"

void sig_handler(int sig);

int main(void){
		
	signal(SIGINT, sig_handler);
	int num;
	
	if(wiringPiSetupGpio() == -1){
		fprintf(stdout, "Unable to start wiringPi GPIO : %s\n", strerror(errno));
		return 1;
	}

	initPir(PIR_PIN);
	
	
	
	
	if (readPir(PIR_PIN) == TRUE)
	{
	delay(50);
	initLcd();
	delay(50);
	printString("Pi security ");
	setDDRAMAddress();
	move2ndLine();
	printString("Pi security ");
	//char a[10];
	//scanf("%s", a);
	//printString(a);
	
	//scanf("%d", &num);
	if(num==0) {
			printf("shut off");
			return 0;}
		else {
			printf("press 0 : shut off");
			}
	
	}
	while(1)
	{
	
	}
	
	return 0;


	
}
//main_textlcd.c

	void sig_handler(int sig)
{
	initLcd();
	exit(0);
}

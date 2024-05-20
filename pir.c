#include "project.h"

int gnPirState = LOW;

void initPir(int nPin)
{
	pinMode(nPin, INPUT);
}

int readPir(int nPin)
{
	int nPirVal = 0;
	nPirVal = digitalRead(nPin);
	
	if (nPirVal == HIGH){
		if(gnPirState == LOW){
			printf("Motion detected!\n");
			gnPirState = HIGH;
		}
	}
	else{
		if(gnPirState == HIGH){
			printf("Motion ended\n");
			gnPirState = LOW;
		}
	}
	
	return nPirVal;
}

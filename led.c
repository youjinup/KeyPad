#include "project.h"

const char LedPinTable[LED_MAX]={LED1, LED2};

void initLed()
{
	int i;
	for(i = 0; i< LED_MAX; i++) {
		pinMode(LedPinTable[i], OUTPUT);
		digitalWrite(LedPinTable[i], LOW);
	}
}

// ledPosition : 0x01~0xFF
void controlLed(int nLedPosition)
{
	int i;
	for(i=0;i<LED_POSITION;i++){
		if(nLedPosition & (1 << i)){
			digitalWrite(LedPinTable[i], HIGH);
		}
		else{
			digitalWrite(LedPinTable[i],LOW);
		}
	}
}




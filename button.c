#include "project.h"

const int ButtonTable[MAX_KEY_BT_NUM] = {
	BUTTON_PIN1,
	BUTTON_PIN2,
	BUTTON_PIN3,
	BUTTON_PIN4
};

void initButton()
{
	int i;
	for(i=0; i < MAX_KEY_BT_NUM; i++) {
		pinMode(ButtonTable[i], INPUT);
	}
}

int readButton()

{
	int i = 0;
	int buttonPin = 0;

	for(i=0;i<MAX_KEY_BT_NUM; i++) {
		if (!digitalRead(ButtonTable[i])) {
			buttonPin |= (1 << i);
		}
	}
	return buttonPin;
}

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>

#define BUTTON_PIN1	23
#define BUTTON_PIN2	24

#define MAX_KEY_BT_NUM	4

void initButton();
int readButton();

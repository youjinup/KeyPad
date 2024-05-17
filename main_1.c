#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>


#include "project.h"

#define PASSWORD_LENGTH 4
#define MAX_DIGITS 4



char setpassword[PASSWORD_LENGTH+1] = "1234";
int currentPosition = 0;
volatile int ledState = 0;

unsigned int fndpattern[10] = {
	0x00, //0
    0x01, // 1
    0x02, // 2
    0x03, // 3
    0x04, // 4
    0x05, // 5
    0x06, // 6
    0x07, // 7
    0x08, // 8
    0x09  // 9
};

void sig_handler(int sig);

void updatefnd(int *digits){
	for(int j=4; j >= 0 ;j--){
		for(int i=0;i <MAX_DIGITS;i++){
		FndData(j, fndpattern[digits[i]], 0);
	}
	}
}

void initFndDisplay() {
    int digits[MAX_DIGITS] = {0};
    updatefnd(digits);
}
PI_THREAD(led){
	while(1){
		if (ledState ==1 ) {
			controlLed(0x01);
			delay(500);
			controlLed(0x02);
			delay(500);
		}
		else {
			controlLed(0x00);
		}
		delay(100);
	}
}

			
int main(void){
	printf("HELLO World\n");
	signal(SIGINT, sig_handler);
	
	if(wiringPiSetupGpio() ==-1) {
		fprintf(stdout, "Unable to start wiringpi GPIO: %s\n", strerror(errno));
		return 1;
	}
	
	//initLcd();
	initLed();
	initPir(PIR_PIN);
	initButton();
	initFnd();
	
	//pthread_t threadId;
	ledState =1;
	piThreadCreate(led);
	
	int digits[MAX_DIGITS] = {0};
	char inputPassword[PASSWORD_LENGTH +1] = {'\0'};
	
	
	
	 
	while(1) {
		
		updatefnd(digits);
		
		
		int motion_Detected  = readPir(PIR_PIN);
		//printf("%d", motion_Detected );
		
		if (motion_Detected != 0){
			ledState =1;
			//initFndDisplay();
			//memset(inputPassword, '\0', sizeof(inputPassword));  // 사용자 비밀번호 초기화			
			
		    while (1) {
				
				
				int buttonStatus = readButton();
				//printf("ButtonStatus: %d\n", buttonStatus);
				delay(100);
				
				if (buttonStatus  ==1){
					digits[currentPosition] = (digits[currentPosition] + 1) % 10;
					updatefnd(digits);
					printf("Button1\n");
				}
				
				if (buttonStatus  == 2){
					//inputPassword[currentPosition] = '0' + digits[currentPosition];
					currentPosition = (currentPosition + 1)% MAX_DIGITS;
					updatefnd(digits);
					printf("Button2\n");
				}
				if (buttonStatus  == 4){
					//memset(digits, 0, sizeof(digits));
					digits = {0,};
					currentPosition = 0;
					updatefnd(digits);
					printf("Button3\n");
				}
				
				if (buttonStatus == 8){
					printf("Button4\n");
					for (int i = 0; i < MAX_DIGITS; i++) {
					inputPassword[i] = '0' + digits[i];
					}
                    
					//inputPassword[MAX_DIGITS] = '\0';
					
					if (strcmp(inputPassword, setpassword) == 0 ) {
						printf("PASS\n");
					}
					else {
						printf("FAIL\n");
					}
				delay(500);
                initFndDisplay();
				break;
				}
					
				}
				
				
			}
			else {
			ledState = 0;
			//pthread_kill(led);

		}
		}
		
	

	
	//pthread_kill(led);
	return 0;
}

void sig_handler(int sig) {
    offFnd();  // 모든 세그먼트 끄기
    exit(0);   // 프로그램 종료
}

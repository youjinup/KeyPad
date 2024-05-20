#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include "project.h"


#define PASSWORD_LENGTH 6

int password[PASSWORD_LENGTH] = { 1, 2, 3, 4, 5, 6 };  // 설정된 비밀번호
int inputPassword[PASSWORD_LENGTH] = { 0 };  // 입력된 비밀번호
int currentPos = 0;  // 현재 비밀번호 입력 위치

void sig_handler(int sig);

int wrong_count = 0;

PI_THREAD(led){
    
	while(1){
        
		if (wrong_count ==1 ) {
			controlLed(0x01);
			delay(5);
		}
		else if (wrong_count ==2 ) {
			controlLed(0x01);
			delay(5);
            controlLed(0x02);
			delay(5);
		}
        else if (wrong_count ==3 ) {
			controlLed(0x01);
			delay(5);
            controlLed(0x02);
			delay(5);
            controlLed(0x04);
			delay(5);
		}
		delay(10);
	}
}


int main(void) {
    signal(SIGINT, sig_handler);

    if (wiringPiSetupGpio() == -1) {
        fprintf(stdout, "Unable to start wiringPi GPIO: %s\n", strerror(errno));
        return 1;
    }

    initButton();
    initFnd();
    initLed();

    int nFndPosition = 0;
    
    while(1) {
    int motion_Detected  = readPir(PIR_PIN);
    
    
    if (motion_Detected) {
               
        while (1) {
            
        piThreadCreate(led);
        
                     
            int buttonState = readButton();

            if (buttonState == 1) {  // BUTTON_PIN1 눌림
                inputPassword[currentPos]++;
                
                if (inputPassword[currentPos] > 9) {
                    inputPassword[currentPos] = 0;
                }
                printf("inputPassword :%d\n", inputPassword[currentPos]);
              
                delay(200);  // 디바운싱을 위한 지연
            }

            if (buttonState == 2) {  // BUTTON_PIN2 눌림
                currentPos++;
                if (currentPos >= PASSWORD_LENGTH) {
                    currentPos = 0;
                }
                printf("currentPos: %d\n", currentPos);
                delay(200);  // 디바운싱을 위한 지연
                
            }

            if (buttonState & (1<< 2)) {  // BUTTON_PIN3 눌림
                for (int i = 0; i < PASSWORD_LENGTH; i++) {
                    inputPassword[i] = 0;
                }
                printf("clear\n");
                currentPos = 0;
                delay(200);  // 디바운싱을 위한 지연
            }

            if (buttonState &(1<<3)) {  // BUTTON_PIN4 눌림
                int isCorrect = 1;
                for (int i = 0; i < PASSWORD_LENGTH; i++) {
                    if (inputPassword[i] != password[i]) {
                        
                        isCorrect = 0;
                        break;
                    }
                }
                
         
                printf("Password Check\n");
                if (isCorrect) {
                    printf("PASS\n");
                 
                }
                else {
                    printf("WRONG\n");
                    wrong_count++;
                    printf("wrong_count: %d\n", wrong_count);
                    
                    
                    if (wrong_count > 3){
                        printf("EXIT\n");
                        initLed();
                        sig_handler(1);
                        
                    }
                    /*
                    if(wrong_count == 1){
                        controlLed(0x01);
                        delay(5000);
                    }
                    
                    else if(wrong_count == 2){
                        
                        controlLed(0x01);
                        delay(5000);
                        controlLed(0x02);
                        delay(5000);
                    }
                    
                    else if(wrong_count == 3){
                        
                        controlLed(0x01);
                        controlLed(0x02);
                        controlLed(0x04);
                        
                    }

                    */
                    
                }
                delay(200);  // 디바운싱을 위한 지연
                
                
            for (int i = 0; i < PASSWORD_LENGTH; i++) {
                printf("%d", inputPassword[i]);
                delay(100);
            }
            printf("\n");
            
            }
    /*
            // FND 데이터 업데이트
            FndData(nFndPosition, inputPassword[nFndPosition]);

            // 다음 FND 위치로 이동
            nFndPosition++;
            
            if (nFndPosition >=PASSWORD_LENGTH) {
                nFndPosition = 0;
            }
    */

            for (int pos=0; pos <PASSWORD_LENGTH; pos++){
                FndData(pos, inputPassword[PASSWORD_LENGTH -1 -pos]);
            }
            
            //delay(1);  // 짧은 지연을 추가하여 깜박임 방지
            
        }
        
     
    }
}

    return 0;
}

void sig_handler(int sig) {
    offFnd();
    exit(0);
}

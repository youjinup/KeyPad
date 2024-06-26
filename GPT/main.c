#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include "fnd.h"
#include "button.h"

#define PASSWORD_LENGTH 6

int password[PASSWORD_LENGTH] = { 1, 2, 3, 4, 5, 6 };  // 설정된 비밀번호
int inputPassword[PASSWORD_LENGTH] = { 0 };  // 입력된 비밀번호
int currentPos = 0;  // 현재 비밀번호 입력 위치

void sig_handler(int sig);

int main(void) {
    signal(SIGINT, sig_handler);

    if (wiringPiSetupGpio() == -1) {
        fprintf(stdout, "Unable to start wiringPi GPIO: %s\n", strerror(errno));
        return 1;
    }

    initButton();
    initFnd();

    int nFndPosition = 0;

    while (1) {
        int buttonState = readButton();

        if (buttonState & (1 << 0)) {  // BUTTON_PIN1 눌림
            inputPassword[currentPos]++;
            if (inputPassword[currentPos] > 9) {
                inputPassword[currentPos] = 0;
            }
            delay(300);  // 디바운싱을 위한 지연
        }

        if (buttonState & (1 << 1)) {  // BUTTON_PIN2 눌림
            currentPos++;
            if (currentPos >= PASSWORD_LENGTH) {
                currentPos = 0;
            }
            delay(300);  // 디바운싱을 위한 지연
        }

        if (buttonState & (1 << 2)) {  // BUTTON_PIN3 눌림
            for (int i = 0; i < PASSWORD_LENGTH; i++) {
                inputPassword[i] = 0;
            }
            currentPos = 0;
            delay(300);  // 디바운싱을 위한 지연
        }

        if (buttonState & (1 << 3)) {  // BUTTON_PIN4 눌림
            int isCorrect = 1;
            for (int i = 0; i < PASSWORD_LENGTH; i++) {
                if (inputPassword[i] != password[i]) {
                    isCorrect = 0;
                    break;
                }
            }
            if (isCorrect) {
                printf("PASS\n");
            }
            else {
                printf("WRONG\n");
            }
            delay(300);  // 디바운싱을 위한 지연
        }

        // FND 데이터 업데이트
        FndData(nFndPosition, inputPassword[nFndPosition]);

        // 다음 FND 위치로 이동
        nFndPosition++;
        if (nFndPosition >= PASSWORD_LENGTH) {
            nFndPosition = 0;
        }

        delay(1);  // 짧은 지연을 추가하여 깜박임 방지
    }

    return 0;
}

void sig_handler(int sig) {
    offFnd();
    exit(0);
}

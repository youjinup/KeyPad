#include "fnd.h"

const int FndSelectTable[MAX_FND_POSITION] = {
    FND_SEL0, FND_SEL1, FND_SEL2, FND_SEL3, FND_SEL4, FND_SEL5
};

const int FndPinTable[MAX_FND_LED] = {
    FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G, FND_DP
};

const int FndNumberTable[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void initFnd() {
    for (int i = 0; i < MAX_FND_POSITION; i++) {
        pinMode(FndSelectTable[i], OUTPUT);
    }
    for (int i = 0; i < MAX_FND_LED; i++) {
        pinMode(FndPinTable[i], OUTPUT);
    }
}

void selectFnd(int position) {
    for (int i = 0; i < MAX_FND_POSITION; i++) {
        digitalWrite(FndSelectTable[i], (position == i) ? LOW : HIGH);
    }
}

void offFnd() {
    for (int i = 0; i < MAX_FND_POSITION; i++) {
        digitalWrite(FndSelectTable[i], HIGH);
    }
}

void FndData(int position, int value) {
    selectFnd(position);  // �־��� ��ġ�� ����
    for (int i = 0; i < MAX_FND_LED; i++) {
        digitalWrite(FndPinTable[i], (FndNumberTable[value] & (1 << i)) ? HIGH : LOW);  // �־��� ���� ���
    }
}

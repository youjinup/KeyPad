#include <wiringPi.h>

#define FND_A 2
#define FND_B 3
#define FND_C 4
#define FND_D 17
#define FND_E 16
#define FND_F 22
#define FND_G 10
#define FND_DP 9

#define FND_SEL0 11
#define FND_SEL1 13
#define FND_SEL2 19
#define FND_SEL3 26
#define FND_SEL4 20
#define FND_SEL5 21

#define A_BIT 0x01
#define B_BIT 0x02
#define C_BIT 0x04
#define D_BIT 0x08
#define E_BIT 0x10
#define F_BIT 0x20
#define G_BIT 0x40
#define DP_BIT 0x80

#define MAX_FND_POSITION 6
#define MAX_FND_LED 8

#define FND_0_SEL 0x01
#define FND_1_SEL 0x02
#define FND_2_SEL 0x04
#define FND_3_SEL 0x08
#define FND_4_SEL 0x10
#define FND_5_SEL 0x20

void initFnd();
void selectFnd(int Position);
void offFnd();
void FndData(int position, long data1, long data2);


#include "project.h"

const int FndSelectTable[MAX_FND_POSITION] = 
{     	
		FND_SEL0, FND_SEL1, FND_SEL2,
		FND_SEL3, FND_SEL4, FND_SEL5,
};

const int FndPinTable[MAX_FND_LED] = 
{     	
		FND_A, FND_B, FND_C, FND_D,
		FND_E, FND_F, FND_G, FND_DP,
		 
};

const int FndNumberTable[16] =
{
	A_BIT|B_BIT|C_BIT|D_BIT|E_BIT|F_BIT,
	B_BIT|C_BIT,
	A_BIT|B_BIT|D_BIT|E_BIT|G_BIT,
	A_BIT|B_BIT|C_BIT|D_BIT|G_BIT,
	B_BIT|C_BIT|F_BIT|G_BIT,
	A_BIT|C_BIT|D_BIT|F_BIT|G_BIT,
	C_BIT|D_BIT|E_BIT|F_BIT|G_BIT,
	A_BIT|B_BIT|C_BIT,
	A_BIT|B_BIT|C_BIT|D_BIT|E_BIT|F_BIT|G_BIT,
	A_BIT|B_BIT|C_BIT|F_BIT|G_BIT,
	A_BIT|B_BIT|C_BIT|E_BIT|F_BIT|G_BIT,
	C_BIT|D_BIT|E_BIT|F_BIT|G_BIT,
	A_BIT|D_BIT|E_BIT|F_BIT,
	B_BIT|C_BIT|D_BIT|E_BIT|G_BIT,
	A_BIT|D_BIT|E_BIT|F_BIT|G_BIT,
	A_BIT|E_BIT|F_BIT|G_BIT,
};

void  initFnd()
{
	int i;
	for(i=0; i < MAX_FND_POSITION; i++) {
				pinMode(FndSelectTable[i], OUTPUT);
			}
			for (i=0; i<MAX_FND_LED; i++) {
				pinMode(FndPinTable[i],OUTPUT);
			}
}
void selectFnd(int Position)
{
	int i;
	for(i=0; i < MAX_FND_POSITION; i++) {
		if (Position & (1 <<i)) {
				digitalWrite(FndSelectTable[i], LOW);
			}
			else {
				digitalWrite(FndSelectTable[i], HIGH);
			}
		}
}
void offFnd()
{
	int i;
	for(i=0; i < MAX_FND_POSITION; i++) {
			digitalWrite(FndSelectTable[i], HIGH);
		}
		
}
/*
void FndData(int position, long data, long data2)
{
	printf ("Fnd position: %d, data : %02X\n", position, data);
	
}
*/


void FndData(int position, long data1, long data2)
{
	printf ("Fnd position: %d, data : %02X\n", position, data1);
	int i;
	int fndData = 0;

	switch (position)
	{
		case 0:
			selectFnd(FND_0_SEL);
			fndData = (data1 & 0x000000ff);
			break;
		case 1:
			selectFnd(FND_1_SEL);
			fndData = (data1 & 0x0000ff00) >> 8;
			break;
		case 2:
			selectFnd(FND_2_SEL);
			fndData = (data1 & 0x00ff0000) >> 16;
			break;
		case 3:
			selectFnd(FND_3_SEL);
			fndData = (data1 & 0xff000000) >> 24;
			break;
		/*case 4:
			selectFnd(FND_4_SEL);
			fndData = (data2 & 0x000000ff);
			break;
		case 5:
			selectFnd(FND_5_SEL);
			fndData = (data2 & 0x0000ff00) >> 8;
			break;
			*/
		default:
			break;
		}
		
		for(i=0; i < MAX_FND_POSITION; i++) {
			if(FndNumberTable[fndData] & (1<<i)){
				digitalWrite(FndPinTable[i], HIGH);
		}
			else{
				digitalWrite(FndPinTable[i], LOW);
		}
	}


	
	delay(1);
}


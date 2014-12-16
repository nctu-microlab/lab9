#include <REG_MPC82G516.H>
#include "tone.h"

#define MIN 8
#define PRO 32

void main() {
	IE = 0x83;
	IT0 = 1;
	TMOD = 0x01;
	TH0 = (65536 - 50000) >> 8;
	TL0 = (65536 - 50000) & 0x00FF;
	
	tone_init();
	tone_onoff(TONE_ON);
	TR0 = 1;
	while(1);
}

unsigned short tone[] = {
	TONE(TONE_C, 5),
	TONE(TONE_D, 5),
	TONE(TONE_E, 5),
	TONE(TONE_F, 5),
	TONE(TONE_G, 5),
	TONE(TONE_A, 5),
	TONE(TONE_B, 5),
	TONE(TONE_C, 6)
};

void timer0_up() interrupt 1 {
	static unsigned char count = 0;
	TH0 = (65536 - 50000) >> 8;
	TL0 = (65536 - 50000) & 0x00FF;
	
	if(++count == 20) {
		P31 = 0;
		P31 = 1;
		count = 0;
	}
}

void get_ad() interrupt 0 {
	unsigned short value = (P2 - MIN) / PRO;
	if(value > 8)
		value = 8;
	P0 = value;
	tone_set(tone[value]);
}

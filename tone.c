#include <REG_MPC82G516.H>
#include "tone.h"

void tone_init() {
	IE |= 0xA0;
	T2CON = 0x08;
	T2MOD = 0x02;

	/* Set default tone to A4 */
	tone_set(TONE(TONE_A, 4));
}

void tone_onoff(bit on_off) {
	TR2 = on_off;
}

void tone_set(unsigned short tone) {
	unsigned short period_m;

	period_m = 3000000 / tone;

	TH2 = 0;
	TL2 = 0;
	RCAP2H = (65536 - period_m) >> 8;
	RCAP2L = (65536 - period_m) & 0x00FF;
}

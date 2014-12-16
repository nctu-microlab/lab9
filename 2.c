#include <REG_MPC82G516.H>
#include "tone.h"

/* TONE, OFFSET, time_interval
 * Example: A4 for 1/2 sec -> {TONE_A, 4, 10} */
typedef unsigned short Sheet[][2];/*
Sheet idata bee_sheet = {
	{TONE(TONE_G, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_E, 4), 20},
	{TONE(TONE_F, 4), 10}, {TONE(TONE_D, 4), 10}, {TONE(TONE_D, 4), 20},
	{TONE(TONE_C, 4), 10}, {TONE(TONE_D, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_F, 4), 10}, {TONE(TONE_G, 4), 10}, {TONE(TONE_G, 4), 10}, {TONE(TONE_G, 4), 20},
	{TONE(TONE_G, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_E, 4), 20},
	{TONE(TONE_F, 4), 10}, {TONE(TONE_D, 4), 10}, {TONE(TONE_D, 4), 20},
	{TONE(TONE_C, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_G, 4), 10}, {TONE(TONE_G, 4), 10}, {TONE(TONE_E, 4), 40},
	{TONE(TONE_D, 4), 10}, {TONE(TONE_D, 4), 10}, {TONE(TONE_D, 4), 10}, {TONE(TONE_D, 4), 10}, {TONE(TONE_D, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_F, 4), 20},
	{TONE(TONE_E, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_F, 4), 10}, {TONE(TONE_G, 4), 20},
	{TONE(TONE_G, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_E, 4), 20},
	{TONE(TONE_F, 4), 10}, {TONE(TONE_D, 4), 10}, {TONE(TONE_D, 4), 20},
	{TONE(TONE_C, 4), 10}, {TONE(TONE_E, 4), 10}, {TONE(TONE_G, 4), 10}, {TONE(TONE_G, 4), 10}, {TONE(TONE_C, 4), 40},
	{0, 0}
};*/

Sheet idata bee_sheet = {
	{TONE(TONE_B, 4), 8}, {TONE(TONE_Ab, 4), 8}, {TONE(TONE_A, 4), 8}, {TONE(TONE_B, 4), 8}, {TONE(TONE_E, 5), 8}, {TONE(TONE_D, 5), 24},
	{TONE(TONE_E, 5), 4}, {TONE(TONE_Gb, 5), 4}, {TONE(TONE_G, 5), 8}, {TONE(TONE_Gb, 5), 8}, {TONE(TONE_E, 5), 8}, {TONE(TONE_G, 5), 8}, {TONE(TONE_D, 5), 24},
	{TONE(TONE_D, 5), 8}, {TONE(TONE_C, 5), 16}, {TONE(TONE_G, 5), 16}, {TONE(TONE_B, 4), 16}, {TONE(TONE_G, 5), 16},
	{TONE(TONE_Gb, 5), 16}, {TONE(TONE_Db, 5), 8}, {TONE(TONE_E, 5), 8}, {TONE(TONE_Eb, 5), 16}, {TONE(TONE_E, 5), 8}, {TONE(TONE_Gb, 5), 8},
	{TONE(TONE_G, 5), 16}, {TONE(TONE_B, 5), 16}, {TONE(TONE_C, 6), 24}, {TONE(TONE_G, 5), 8}, {TONE(TONE_Gb, 5), 24}, {TONE(TONE_G, 5), 4}, {TONE(TONE_A, 5), 5}, {TONE(TONE_B, 5), 24},
	{TONE(TONE_G, 5), 4}, {TONE(TONE_Gb, 5), 4}, {TONE(TONE_E, 5), 8}, {TONE(TONE_Gb, 5), 8}, {TONE(TONE_G, 5), 8}, {TONE(TONE_C, 5), 8}, {TONE(TONE_A, 5), 24},
	{TONE(TONE_G, 5), 8}, {TONE(TONE_Gb, 5), 8}, {TONE(TONE_E, 5), 8}, {TONE(TONE_Eb, 5), 16}, {TONE(TONE_E, 5), 40}
};


unsigned short next_note;

void main() {
	IE = 0x82;
	TMOD = 0x01;
	TH0 = (65536 - 30000) >> 8;
	TL0 = (65536 - 30000) & 0x00FF;

	tone_init();
	next_note = 0;
	TR0 = 1;
 	while(1);
}

void timer0_up() interrupt 1 {
	static unsigned char remain_count = 0;
	unsigned short *this_sheet;
	TH0 = (65536 - 30000) >> 8;
	TL0 = (65536 - 30000) & 0x00FF;

	if(!remain_count) {
		this_sheet = bee_sheet[next_note];
		if(this_sheet[0] == 0 && this_sheet[1] == 0) {
			next_note = 0;
			
			this_sheet = bee_sheet[next_note];
		}

		next_note++;
		tone_set(this_sheet[0]);
		remain_count = this_sheet[1];
		tone_onoff(TONE_ON);
	} else if (remain_count == 1) {
		tone_onoff(TONE_OFF);
	}

	remain_count--;
}

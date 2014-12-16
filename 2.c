#include <REG_MPC82G516.H>
#include "tone.h"

/* TONE, OFFSET, time_interval
 * Example: A4 for 1/2 sec -> {TONE_A, 4, 10} */
typedef unsigned short Sheet[][3];
Sheet bee_sheet = {
	{TONE_G, 4, 10}, {TONE_E, 4, 10}, {TONE_E, 4, 20},
	{TONE_F, 4, 10}, {TONE_D, 4, 10}, {TONE_D, 4, 20},
	{TONE_C, 4, 10}, {TONE_D, 4, 10}, {TONE_E, 4, 10}, {TONE_F, 4, 10}, {TONE_G, 4, 10}, {TONE_G, 4, 10}, {TONE_G, 4, 20},
	{TONE_G, 4, 10}, {TONE_E, 4, 10}, {TONE_E, 4, 20},
	{TONE_F, 4, 10}, {TONE_D, 4, 10}, {TONE_D, 4, 20},
	{TONE_C, 4, 10}, {TONE_E, 4, 10}, {TONE_G, 4, 10}, {TONE_G, 4, 10}, {TONE_E, 4, 40},
	{TONE_D, 4, 10}, {TONE_D, 4, 10}, {TONE_D, 4, 10}, {TONE_D, 4, 10}, {TONE_D, 4, 10}, {TONE_E, 4, 10}, {TONE_F, 4, 20},
	{TONE_E, 4, 10}, {TONE_E, 4, 10}, {TONE_E, 4, 10}, {TONE_E, 4, 10}, {TONE_E, 4, 10}, {TONE_F, 4, 10}, {TONE_G, 4, 20},
	{TONE_G, 4, 10}, {TONE_E, 4, 10}, {TONE_E, 4, 20},
	{TONE_F, 4, 10}, {TONE_D, 4, 10}, {TONE_D, 4, 20},
	{TONE_C, 4, 10}, {TONE_E, 4, 10}, {TONE_G, 4, 10}, {TONE_G, 4, 10}, {TONE_C, 4, 40},
	{0, 0, 0}
};

Sheet tos_sheet = {
	{TONE_B, 4, 10}, {TONE_Ab, 4, 10}, {TONE_A, 4, 10}, {TONE_B, 4, 10}, {TONE_E, 5, 10}, {TONE_D, 5, 30},
	{TONE_E, 5, 5}, {TONE_Gb, 5, 5}, {TONE_G, 5, 10}, {TONE_Gb, 5, 10}, {TONE_E, 5, 10}, {TONE_G, 5, 10}, {TONE_D, 5, 30},
	{TONE_D, 5, 10}, {TONE_C, 5, 20}, {TONE_G, 5, 20}, {TONE_B, 4, 20}, {TONE_G, 5, 20},
	{TONE_Gb, 5, 20}, {TONE_Db, 5, 10}, {TONE_E, 5, 10}, {TONE_Eb, 5, 20}, {TONE_E, 5, 10}, {TONE_Gb, 5, 10},
	{TONE_G, 5, 20}, {TONE_B, 5, 20}, {TONE_C, 6, 30}, {TONE_G, 5, 10}, {TONE_Gb, 5, 30}, {TONE_G, 5, 5}, {TONE_A, 5, 5}, {TONE_B, 5, 30},
	{TONE_G, 5, 5}, {TONE_Gb, 5, 5}, {TONE_E, 5, 10}, {TONE_Gb, 5, 10}, {TONE_G, 5, 10}, {TONE_C, 5, 10}, {TONE_A, 5, 30},
	{TONE_G, 5, 10}, {TONE_Gb, 5, 10}, {TONE_E, 5, 10}, {TONE_Eb, 5, 20}, {TONE_E, 5, 50}
};

Sheet *sheet[] = {
	bee_sheet, tos_sheet
};

unsigned short next_note;
unsigned short now_sheet;
#define SHEET_MAX 2

void next_note();

void main() {
	IE = 0x82;
	TMOD = 0x01;
	TH0 = (65536 - 50000) >> 8;
	TL0 = (65536 - 50000) & 0x00FF;

	tone_init();
	now_note = 0;
	now_sheet = 0;
	TR0 = 1;
}

void timer0_up() interrupt 1 {
	static unsigned char remain_count = 0;
	unsigned short *this_sheet;
	TH0 = (65536 - 50000) >> 8;
	TL0 = (65536 - 50000) & 0x00FF;

	if(!remain_count) {
		this_sheet = sheet[now_sheet][next_note];
		if(this_sheet[0] == 0 && this_sheet[1] == 0 && this_sheet[2] == 0) {
			next_note = 0;

			if(++now_sheet >= SHEET_MAX) {
				now_sheet = 0;
			}
			this_sheet = sheet[now_sheet][next_note];
		}

		next_note++;
		tone_set(this_sheet[0], this_sheet[1]);
		remain_count = this_sheet[2];
		tone_onoff(TONE_ON);
	} else if (remain_count == 1) {
		tone_onoff(TONE_OFF);
	}

	remain_count--;
}

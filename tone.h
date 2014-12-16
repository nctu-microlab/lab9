#pragma once

#define TONE_ON 1
#define TONE_OFF 0

/* Define C7~B7 */
#define TONE_C 2093
#define TONE_Db 2217
#define TONE_D 2349
#define TONE_Eb 2489
#define TONE_E 2637
#define TONE_F 2794
#define TONE_Gb 2960
#define TONE_G 3136
#define TONE_Ab 3322
#define TONE_A 3520
#define TONE_Bb 3729
#define TONE_B 3951


void tone_init();

/* tone_onoff(TONE_ON) to start making tone.
 * tone_onoff(TONE_OFF) to turn it off. */
void tone_onoff(bit on_off);

/* Example: tone_set(TONE_A, 4) to set tone to A4. */
void tone_set(unsigned short tone, unsigned char offset);

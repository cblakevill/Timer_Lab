#include <msp430fr5739.h>
#include "TimeTest.h"

void TimeTestInit(void)
{
TA1CTL = MC_2 + ID_0 + TASSEL_2; //continuous mode
}

#define TimeTestOffset (22)

void TimeTestStart(TimeTest *timer)
{
	timer->oldtcnt = TA1R;
}

void TimeTestEnd(TimeTest *timer)
{
	int newtcnt;
	//If called before TimeTestStart leave now
	// If the tcnt value is zero and no previous count get out
	if (!((timer->oldtcnt == 0)&&(timer->count == 0))) {
		newtcnt = TA1R;
		timer->count += 1; // increment count
		newtcnt -= (timer->oldtcnt + TimeTestOffset);
		timer->totaltime += newtcnt;
		if (timer->count == 1) { // If first time through
			timer->min = newtcnt;
			timer->max = newtcnt;
			timer->mincount = 1;
			timer->maxcount = 1;
			}
		if( newtcnt < timer->min) { // New minimum
				timer->min = newtcnt;
				timer->mincount = 1;
				}
		if( newtcnt == timer->min ) {
				timer->mincount++;} //another at minimum
		if( newtcnt > timer->max) { // New maximum
				timer->max = newtcnt;
				timer->maxcount = 1;
				}
		if( newtcnt == timer->max ) {
				timer->maxcount++; } // another at maximum
	}
}

void timeoutDetect(TimeTest *timer){
	TimeTestEnd(timer);
	if(timer->totaltime > 40000)
	{
		TimeTestInit();
		timer->count = 0;
		timer->max = 0;
		timer->maxcount = 65535;
		timer->min = 0;
		timer->mincount = 0;
		timer->oldtcnt = 0;
		timer->totaltime = 0;
		PJOUT ^= BIT0;
	}
	TimeTestStart(timer);
}

#include <msp430fr5739.h>
#include "TimeTest.h"

main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	static TimeTest TT = {0, 0, 65535, 0, 0, 0, 0};
	PJDIR = BIT0;
	PJOUT = 0x00;
	TimeTestInit();

	TimeTestStart(&TT);
	while (1)
	{
		//detect timeout after 40,000 cycles pass
		//reset timeout timer after each timeout
		timeoutDetect(&TT);
	}
}

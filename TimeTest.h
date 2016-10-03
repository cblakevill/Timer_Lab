#ifndef timefuncs
  #define timefuncs

 typedef struct {unsigned int oldtcnt;
 	 	 	 	 unsigned int count;
 	 	 	 	 unsigned int min;
 	 	 	 	 unsigned int mincount;
 	 	 	 	 unsigned int max;
 	 	 	 	 unsigned int maxcount;
 	 	 	 	 unsigned int totaltime;} TimeTest ;

// Structure initialised as follows
// { 0, 0, 65535, 0, 0, 0, 0}

// Initialise the timing for the system
void TimeTestInit(void);
//Start the timer
void TimeTestStart(TimeTest *timer);
//End the timer
void TimeTestEnd(TimeTest *timer);
//Set a timeout
void timeoutDetect(TimeTest *timer);

#endif

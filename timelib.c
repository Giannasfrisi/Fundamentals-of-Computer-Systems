/*******************************************************************************
* Time Functions Library (implementation)
*
* Description:
*     A library to handle various time-related functions and operations.
*
* Author:
*     Renato Mancuso <rmancuso@bu.edu>
*
* Affiliation:
*     Boston University
*
* Creation Date:
*     September 10, 2023
*
* Notes:
*     Ensure to link against the necessary dependencies when compiling and
*     using this library. Modifications or improvements are welcome. Please
*     refer to the accompanying documentation for detailed usage instructions.
*
*******************************************************************************/

#include "timelib.h"

/* Return the number of clock cycles elapsed when waiting for
 * wait_time seconds using sleeping functions */
uint64_t get_elapsed_sleep(long sec, long nsec)
{
	/* IMPLEMENT ME! */
    struct timespec t;
    uint64_t start;
	get_clocks(start);  
    t.tv_sec = sec;
    t.tv_nsec = nsec;
    nanosleep(&t, NULL);
    uint64_t end; 
	get_clocks(end);
    return end - start;
}

/* Return the number of clock cycles elapsed when waiting for
 * wait_time seconds using busy-waiting functions */
uint64_t get_elapsed_busywait(long sec, long nsec)
{
	/* IMPLEMENT ME! */
	struct timespec start_time, current_time;
    uint64_t start_clocks; 
	

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    get_clocks(start_clocks);  

        // Initialize target_time by adding the start time and wait time
    struct timespec target_time = start_time;
    target_time.tv_sec += sec;
    target_time.tv_nsec += nsec;

    // Normalize the timespec structure
    if (target_time.tv_nsec >= NANO_IN_SEC) {
        target_time.tv_nsec -= NANO_IN_SEC;
        target_time.tv_sec++;
    }

    while (1) {
        // Get the current time
        clock_gettime(CLOCK_MONOTONIC, &current_time);

        // Check if the current time is greater than or equal to the target time
        if ((current_time.tv_sec > target_time.tv_sec) || 
            (current_time.tv_sec == target_time.tv_sec && current_time.tv_nsec >= target_time.tv_nsec)) {
            break;
        }
    }

    uint64_t end_clocks;
	get_clocks(end_clocks);
    return end_clocks - start_clocks;
}

/* Utility function to add two timespec structures together. The input
 * parameter a is updated with the result of the sum. */
void timespec_add (struct timespec * a, struct timespec * b)
{
	/* Try to add up the nsec and see if we spill over into the
	 * seconds */
	time_t addl_seconds = b->tv_sec;
	a->tv_nsec += b->tv_nsec;
	if (a->tv_nsec > NANO_IN_SEC) {
		addl_seconds += a->tv_nsec / NANO_IN_SEC;
		a->tv_nsec = a->tv_nsec % NANO_IN_SEC;
	}
	a->tv_sec += addl_seconds;
}

/* Utility function to compare two timespec structures. It returns 1
 * if a is in the future compared to b; -1 if b is in the future
 * compared to a; 0 if they are identical. */
int timespec_cmp(struct timespec *a, struct timespec *b)
{
	if(a->tv_sec == b->tv_sec && a->tv_nsec == b->tv_nsec) {
		return 0;
	} else if((a->tv_sec > b->tv_sec) ||
		  (a->tv_sec == b->tv_sec && a->tv_nsec > b->tv_nsec)) {
		return 1;
	} else {
		return -1;
	}
}

/* Busywait for the amount of time described via the delay
 * parameter */
uint64_t busywait_timespec(struct timespec delay)
{
	/* IMPLEMENT ME! (Optional but useful) */
	struct timespec start_time, current_time;
    uint64_t start_clocks;
	get_clocks(start_clocks);  

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    struct timespec target_time = start_time;
    timespec_add(&target_time, &delay);  

    while (1) {
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        if (timespec_cmp(&current_time, &target_time) >= 0) {
            break;
        }
    }

    uint64_t end_clocks;
	get_clocks(end_clocks);
    return end_clocks - start_clocks;
}

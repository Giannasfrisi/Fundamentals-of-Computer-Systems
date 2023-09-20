/*******************************************************************************
* CPU Clock Measurement Using RDTSC
*
* Description:
*     This C file provides functions to compute and measure the CPU clock using
*     the `rdtsc` instruction. The `rdtsc` instruction returns the Time Stamp
*     Counter, which can be used to measure CPU clock cycles.
*
* Author:
*     Renato Mancuso
*
* Affiliation:
*     Boston University
*
* Creation Date:
*     September 10, 2023
*
* Notes:
*     Ensure that the platform supports the `rdtsc` instruction before using
*     these functions. Depending on the CPU architecture and power-saving
*     modes, the results might vary. Always refer to the CPU's official
*     documentation for accurate interpretations.
*
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "timelib.h"

int main (int argc, char ** argv)
{
	/* IMPLEMENT ME! */
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <seconds> <nanoseconds> <s|b>\n", argv[0]);
        return EXIT_FAILURE;
    }

	long sec = atol(argv[1]);
    long nsec = atol(argv[2]);
    char method = argv[3][0];

	uint64_t elapsed_clocks = 0;
    if (method == 's') {
        elapsed_clocks = get_elapsed_sleep(sec, nsec);  
    } else if (method == 'b') {
        elapsed_clocks = get_elapsed_busywait(sec, nsec);  
    } else {
        fprintf(stderr, "Invalid method. Use 's' for sleep-based or 'b' for busy-waiting.\n");
        return EXIT_FAILURE;
    }

	//Clock speed 
	double elapsed_time = (double)sec + ((double)nsec / 1e9);  // Total elapsed time in seconds
    double clock_speed_mhz = (double)elapsed_clocks / (elapsed_time * 1e6);
   
	//Printing output
	printf("WaitMethod: %s\n", method == 's' ? "SLEEP" : "BUSYWAIT");
    printf("WaitTime: %ld %ld\n", sec, nsec);
    printf("ClocksElapsed: %lu\n", elapsed_clocks);
    printf("ClockSpeed: %lf\n", clock_speed_mhz);

	return EXIT_SUCCESS;
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "command-line-options.h"
#include "ibarland-utils.h"

/**
 * invLogSum.c
 *
 * Proj3 - Concurrency via Threads
 * Due: Thursday, March 24th, 2016 @ 2p
 * Author: Forrest Meade (fmeade)
 * 
 * Description: 
 *
 * Help: 
 * 
 */
/* The possible command-line options to the program. 
 */
struct option_info options[] =
  {  { "num-threads",  'n',  "1", "the number of threads to create. " }
    ,{ "stop",  's',  "2000000000", "the upper limit of the sum. " } 
  };

#define NUM_OPTIONS SIZEOF_ARRAY(options)


 int main(int argc, char** argv) {
 	char** settings = allOptions( argc, argv, NUM_OPTIONS, options );
    // Now, the array `settings` contains all the options, in order:
    // either taken from the command-line, or from the default given in `options[]`.

    if(atoi(settings[0]) < 1) {
    	printf("%s\n", "ERROR: Not a positive number.");
    	exit(-1);
    }

    if(atoi(settings[1]) < 2) {
    	printf("%s\n", "ERROR: Not larger than 2.");
    	exit(-1);
    }





 	return 0;
 }
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

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

    const int NUM_THREADS = atoi(settings[0]);
    const int STOP = atoi(settings[1]);

    if(NUM_THREADS < 1) {
    	printf("%s\n", "ERROR: Not a positive number.");
    	exit(-1);
    }

    if(STOP < 2) {
    	printf("%s\n", "ERROR: Not larger than 2.");
    	exit(-1);
    }

    time_t t0, t1;
    t0 = time_usec(NULL);


    pthread_t* tids = malloc( NUM_THREADS * sizeof(pthread_t) );   // pthread_t[]

    pthread_attr_t attr; 

    /* get the default attributes */ 
    pthread_attr_init(&attr);

    int i;
    /* create the threads */
    for (i = 0;  i < NUM_THREADS;  ++i)  {
        int* iToPass = malloc(sizeof(int));
        *iToPass = i;
        pthread_create(&tids[i], &attr, solve, (void*) &*iToPass); 
    }



  
    double* result;
    /* now join on each thread */
    for (i = 0;  i < numThreads;  ++i) {
        pthread_join( tids[i], (void**) &result ); 
        printf("Thread %d returned %f.\n", i, *result);
        // Now that we've used the result, we can free the memory used to hold the result:
        free(&*result);
    }


/* Solves the problem in one stride

    double sum = 0;
    int i;

    for(i = 2; i < STOP; i++) {
        sum = sum + (1 / log(i));
    }
*/
    t1 = time_usec(NULL);

    printf("%s%f\n", "Sum: ", sum);
    printf("%s%ld%s\n", "Wall Time: ", (long)(t1 - t0), " milliseconds");
    printf("%s%d\n", "Number of Threads: ", NUM_THREADS);
    printf("%s%d\n", "Upper Limit of Sum: ", STOP);

 	return 0;
 }

 void* solve() {

 }
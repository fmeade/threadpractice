#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

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

typedef struct {
    int lower;
    int upper;
} bounds;

 void* solve(void* param) {

    bounds* boundaries = (bounds*) param;
    bounds temp = *boundaries;

    free(&*boundaries);

    double *sum = malloc(sizeof(double));

    int i;
    for (i = temp.lower; i <= temp.upper; ++i) {
        *sum = *sum + (1 / log(i));
    }
    

    pthread_exit(&*sum);

 }

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

    int split = ((STOP - 1) / NUM_THREADS);
    int splitCheck = ((STOP - 1) % NUM_THREADS);
    int i;
    /* create the threads */
    for (i = 0;  i < NUM_THREADS;  ++i)  {
        bounds* itemsToPass = malloc(sizeof(bounds));

        if(i == 0) {
            itemsToPass->lower = 2;
        }
        else {
            itemsToPass->lower = (split * i) + 1;
        }

        itemsToPass->upper = (split * (i + 1));

        if ((splitCheck != 0) && (itemsToPass->upper == (STOP-2))) {

            itemsToPass->upper = itemsToPass->upper + 1;
        }

        pthread_create(&tids[i], &attr, solve, (void*) &*itemsToPass); 
    }



  
    double* result;
    double sum = 0;
    /* now join on each thread */
    for (i = 0;  i < NUM_THREADS;  ++i) {

        pthread_join( tids[i], (void**) &result ); 
        sum = sum + *result;

        // Now that we've used the result, we can free the memory used to hold the result:
        free(&*result);
    }





    t1 = time_usec(NULL);

    printf("%s%f\n", "Sum: ", sum);
    printf("%s%ld%s\n", "Wall Time: ", (long)(t1 - t0), " milliseconds");
    printf("%s%d\n", "Number of Threads: ", NUM_THREADS);
    printf("%s%d\n", "Upper Limit of Sum: ", STOP);

 	return 0;
 }
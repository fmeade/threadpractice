import java.math.*;

/**
 * invLogSum.java
 *
 * Proj3 - Concurrency via Threads
 * Due: Thursday, March 24th, 2016 @ 2p
 * Author: Forrest Meade (fmeade)
 * 
 * Description: A program tha solves the equation below by distributing the work
 *				across a specified number of threads.
 *
 * 				stop-1
 * 				∑ (1/ ln(i))
 * 				i=2
 * 				
 * Help: http://www.radford.edu/~itec371/2016spring-ibarland/Lectures/c-examples/ZzCounter.java
 * 
 */
public class InvLogSum {

	private static double finalSum;


	/* The possible command-line options to the program. */
	static CommandLineOption[] options = {
        new CommandLineOption( "num-threads", 'n', "1", "the number of threads to create." ),
        new CommandLineOption( "stop", 's', "2000000000", "the upper limit of the sum." )       
    };

	
	public static void main(String[] args) throws InterruptedException {

		String[] settings = CommandLineOption.allOptions( args, options );
        // Now, the array `settings` contains all the options, in order:
        // either taken from the command-line, or from the default given in `options[]`.

		final int NUM_THREADS = Integer.parseInt(settings[0]);
	    final long STOP = Integer.parseInt(settings[1]);

	    if(NUM_THREADS < 1) {
	    	System.out.printf("%s\n", "ERROR: Not a positive number.");
	    	System.exit(-1);
	    }

	    if(STOP < 2) {
	    	System.out.printf("%s\n", "ERROR: Not larger than 2.");
	    	System.exit(-1);
	    }



	    long t0, t1;

	    t0 = System.nanoTime();


	    long split = ((STOP - 1) / NUM_THREADS);
    	long splitCheck = ((STOP - 1) % NUM_THREADS);
    	long lower, upper;

    	LogThread threads[] = new LogThread[NUM_THREADS];



    	/* create the threads */
	    for (int i = 0;  i < NUM_THREADS;  i++)  {

	        if(i == 0) {
	            lower = 2;
	        }
	        else {
	            lower = (split * i) + 1;
	        }

	        upper = (split * (i + 1));

	        if ((splitCheck != 0) && (upper == (STOP-2))) {

	            upper = upper + 1;
	        }

	        threads[i] = new LogThread(lower, upper);
	        threads[i].start();
	    }

	    double tempSum = 0.0;

		/* joins the threads and adds thread results */
	    for (int i = 0;  i < NUM_THREADS;  ++i)  {

	        threads[i].join();
	        tempSum = tempSum + threads[i].answer();
	    }	    

	    finalSum = tempSum;


	    t1 = System.nanoTime();
	    long wallTime = (t1 - t0) / 1000000;



		System.out.printf("%s%f\n", "Sum: ", finalSum);
	    System.out.printf("%s%d%s\n", "Wall Time: ", wallTime, " milliseconds");
	    System.out.printf("%s%d\n", "Number of Threads: ", NUM_THREADS);
	    System.out.printf("%s%d\n", "Upper Limit of Sum: ", STOP);
	    System.out.printf("%s%d\n", "Available Processors: ",  Runtime.getRuntime().availableProcessors());
	}

}


	/* class to extend thread for natural log summation calculation
	 */
	class LogThread extends Thread {

		long lowerBound;
		long upperBound;

		private double sumForThread;

		LogThread(long _lowerBound, long _upperBound) {
			lowerBound = _lowerBound;
			upperBound = _upperBound;
		}

		public void run() {

			double sumSoFar = 0.0;

	    	for(long i = lowerBound; i <= upperBound; i++) {
	        	sumSoFar = sumSoFar + (1 / Math.log(i));
	    	}

	    	sumForThread = sumSoFar;
		}

		public double answer() {
			return sumForThread;
		}

	}
import java.util.*;
import java.math.*;

/**
 * invLogSum.java
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
public class InvLogSum {

	/* The possible command-line options to the program. */
	static CommandLineOption[] options = {
        new CommandLineOption( "num-threads", 'n', "1", "the number of threads to create." ),
        new CommandLineOption( "stop", 's', "2000000000", "the upper limit of the sum." )       
    };
	
	public static void main(String[] args) {

		String[] settings = CommandLineOption.allOptions( args, options );
        // Now, the array `settings` contains all the options, in order:
        // either taken from the command-line, or from the default given in `options[]`.

		final int NUM_THREADS = Integer.parseInt(settings[0]);
	    final int STOP = Integer.parseInt(settings[1]);

	    if(NUM_THREADS < 1) {
	    	System.out.printf("%s\n", "ERROR: Not a positive number.");
	    	System.exit(-1);
	    }

	    if(STOP < 2) {
	    	System.out.printf("%s\n", "ERROR: Not larger than 2.");
	    	System.exit(-1);
	    }

	    long t0, t1;

	    t0 = System.currentTimeMillis();

	    double sum = 0;

	    for(int i = 2; i < STOP; i++) {
	        sum = sum + (1 / Math.log(i));
	    }

	    t1 = System.currentTimeMillis();


		System.out.printf("%s%f\n", "Sum: ", sum);
	    System.out.printf("%s%d%s\n", "Wall Time: ", (t1 - t0), " milliseconds");
	    System.out.printf("%s%d\n", "Number of Threads: ", NUM_THREADS);
	    System.out.printf("%s%d\n", "Upper Limit of Sum: ", STOP);
	    System.out.printf("%s%d\n", "Available Processors: ",  Runtime.getRuntime().availableProcessors());
	}
}
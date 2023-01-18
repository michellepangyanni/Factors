/*
 * COMP 321 Project 1: Factors
 *
 * This program computes the number of prime factors, and optionally the number
 * of distinct prime factors, for an unsigned integer input.
 * 
 * <Michelle Pang, yp29>
 */

#include <assert.h>
#include <math.h>     // Included in case you use the standard math library.
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static unsigned int	count_distinct_factors(unsigned int n);
static unsigned int	count_factors(unsigned int n);
static unsigned int	count_factors_recursive(unsigned int n);
static void		test_factors(void);

// Replace this comment with any global variable declarations.

// Replace this comment with any helper functions.
/*
Effects:
	Return the prime factor found by incrementing factor and dividing num by each of the factor recursively
*/
static unsigned int
count_factors_helper(unsigned int num, unsigned int factor, unsigned int counter){
		// Base case: reached the last prime factor
		if (num / factor < 2){
				counter ++;
				return (counter);
		}
		// Recursive step: 
		// Case1: when num is not prime, then it is still divisible by factor
		if (num % factor == 0){
				counter ++;
				return (count_factors_helper(num / factor, factor, counter));
		}
		// Case2: when the num could be prime, then increment counter until we find Case1 or find that num is prime
		// that its only prime factor is itself
		else {
				return (count_factors_helper(num, factor + 1, counter));
		}
}

/*
Effect:
	Return false if n is not in array, return truth if n is in array
*/
static int
include(int arr[], size_t arraySize, int n){
		//int arrSize = sizeof(arr);
		for(int i = 0; i < arraySize; i ++){
				if (arr[i] == n){
						return (1);
				}
		}
		return (0);
}
/* 
 * Requires:  
 *   The input "n" must be greater than 1.
 *
 * Effects: 
 *   Returns the number of factors of the input "n".
 */
static unsigned int
count_factors_recursive(unsigned int n)
{
	// Replace this comment with your local variable declarations.

	assert(n > 1);
	// Upper bound for the total possible number of primes
	/*
	 * Replace this comment with your code.
	 */
	return (count_factors_helper(n, 2, 0));
}

/* 
 * Requires:  
 *   The input "n" must be greater than 1.
 *
 * Effects: 
 *   Returns the number of factors of the input "n".
 */
static unsigned int
count_factors(unsigned int n)
{
	// Replace this comment with your local variable declarations.
    int counter = 0;
	assert(n > 1);
	
	//Divide n by 2, the lowest prime number, until it could not be divided anymore
	while (n % 2 == 0){
			n = n /2;
			counter ++;
	}
	// Divide n by each odd number until it could not be divided anymore
	for (int i = 3; i < sqrt(n); i += 2){
			while (n % i == 0){
					n /= i;
					counter ++;
			}
			
	}
	// When n is a prime and is greater than 2
	if(n > 2){
			counter ++;
	}
	
	return (counter);
}

/* 
 * Requires:  
 *   The input "n" must be greater than 1.
 *
 * Effects: 
 *   Returns the number of distinct factors of the input "n".
 */
static unsigned int
count_distinct_factors(unsigned int n)
{
	// Replace this comment with your local variable declarations.

	assert(n > 1);
	int upper_bound = ceil(sqrt(n));
	// Array that holds all possible primes
	int primes[upper_bound];

	// Set each element in primes array to 0
	for (int i = 0; i < upper_bound; i++){
			primes[i] = 0;
	}

	// track first empty index
	int empty_index = 0;
	// track number of distinct primes
	int counter = 0;

	//Divide n by 2, the lowest prime number, until it could not be divided anymore
	while (n % 2 == 0){
			n /= 2;
			if (include(primes, upper_bound, 2) == 0){
					counter++;
					primes[empty_index] = 2;
					empty_index++;
			}
	}
	// Divide n by each odd number until it could not be divided anymore
	for (int i = 3; i <= sqrt(n); i += 2){
			while (n % i == 0){
					n /= i;
					if (include(primes, upper_bound, i) == 0){
						counter++;
						primes[empty_index] = i;
						empty_index++;

					}
			}	
	}
	// When n is a prime and is greater than 2
	if(n > 2){
			if (include(primes, upper_bound, n) == 0){
					counter++;
					primes[empty_index] = n;
					empty_index++;
			}
			
	} 

	/*
	 * Replace this comment with your code.  Also, don't forget to modify
	 * the following statement to return the actual number of distinct
	 * factors.
	 */
	return (counter);
}

/* 
 * Requires:
 *   Nothing.
 *
 * Effects:
 *   Runs testing procedures.  Currently only prints a message.
 */
static void
test_factors(void)
{

	printf("Test Factors\n");
}

/* 
 * Requires:
 *   Nothing.
 *
 * Effects:
 *   If the "-t" option is specified on the command line, then test code is
 *   executed and the program exits.
 *   
 *   Otherwise, requests a number from standard input.  If the "-r" option is
 *   specified on the command line, then prints the number of prime factors
 *   that the input number has, calculated using a recursive function.
 *   Otherwise, prints the number of prime factors that the input number has
 *   and the number of those factors that are distinct using iterative
 *   functions.
 *
 *   Upon completion, the program always returns 0.
 *
 *   If the number that is input is not between 2 and the largest unsigned
 *   integer, the output of the program is undefined, but it will not crash.
 */
int
main(int argc, char **argv)
{
	unsigned int n;
	int c;
	bool recursive = false;
	bool runtests = false;

	// Parse the command line.
	while ((c = getopt(argc, argv, "rt")) != -1) {
		switch (c) {
		case 'r':             // Use recursive version.
			recursive = true;
			break;
		case 't':             // Run test procedure and exit.
			runtests = true;
			break;
		default:
			break;
		}
	}

	// If "-t" is specified, run test procedure and exit program.
	if (runtests) {
		test_factors();
		return (0);
	}

	// Get input.
	printf("Enter number:\n");
	if (scanf("%u", &n) != 1) {
		fprintf(stderr, "Input error\n");
		return (1);
	}

	// Validate the input.
	if (n < 2) {
		fprintf(stderr, "Invalid input: %u\n", n);
		return (1);
	}

	// Print results.
	if (recursive) {
		// Use recursive version.
		printf("%u has %u prime factors.\n",
		    n, count_factors_recursive(n));
	} else {
		// Use iterative versions.
		printf("%u has %u prime factors, %u of them distinct.\n",
		    n, count_factors(n), count_distinct_factors(n));
	}

	// Report no errors.
	return (0);
}

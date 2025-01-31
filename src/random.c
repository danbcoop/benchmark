#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef enum pattern_type {
    SEQUENTIAL,
    STRIDED,
    RANDOM,
} pattern_type;

pattern_type generate_pattern(int ratio_seq, int ratio_stride, int ratio_rand) {
    double r = (double) rand()/RAND_MAX;
    r *= (ratio_rand + ratio_seq + ratio_stride);
    if (r < ratio_rand) {
        return RANDOM;
    } else if (r < ratio_rand + ratio_stride) {
        return STRIDED;
    }
    return SEQUENTIAL;
}

double harmonic(int n) {
	double H = 0.0;
	for (int i = 1; i <= n; i++) {
		H += 1.0 / i;
	}
	return H;
}

/* Returns a uniformly distributed number between 0 and N, excluding N:
 * [0, N) */
int uniform(int N) {
    return ((double)rand()/RAND_MAX)*N;
}

double uniform_double() {
    return ((double)rand()/RAND_MAX);
}

// Function to randomize an array
void shuffle_array(uint64_t *array, uint64_t N) {
    // Shuffle the array using the Fisher-Yates algorithm
    for (int i = N - 1; i > 0; i--) {
        int j = uniform(i + 1);
        // Swap arr[i] and arr[j]
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
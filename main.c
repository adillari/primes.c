#include <stdio.h>
#include <stdlib.h>

void print_int_array(int* array, int size) {
    for (int iterator = 0; iterator < size; iterator++)
    {
        printf("%d\n", array[iterator]);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./primes {int less than INT_MAX-1}\n");
        return 1;
    }

    const int LIMIT = atoi(argv[1]);

    int *integers = malloc(sizeof(int) * LIMIT);

    if (integers == NULL)
    {
        printf("malloc failed\n");
        return 1;
    }

    // fill our array with integers starting from 2
    for (int iterator = 0; iterator < LIMIT; iterator++)
    {
        integers[iterator] = iterator+2;
    }

    // iterate through integers...
    for (int iterator = 0; iterator < LIMIT; iterator++)
    {
        int integer = integers[iterator];

        if (integer == 0) continue;

        printf("filtering out multiples of %d\n", integer);

        // and convert any multiples of integers to 0
        int multiple = integer;
        while (true) {
            multiple += integer;

            if (multiple > LIMIT+1) break;
            if (integers[multiple-2] == 0) continue;

            printf("setting %d to 0\n", integers[multiple-2]);
            integers[multiple-2] = 0; // -2 because 2 is at index 0, 3 is at 1, etc
        }
    }

    // integers array should only be prime numbers now

    // lets count how many primes exist in the array, and
    // allocate a new smaller array just to house these primes

    // count 'em
    int num_primes = 0;
    for (int iterator = 0; iterator < LIMIT; iterator++)
    {
        if (integers[iterator] != 0)
            num_primes++;
    }

    // allocate it
    int *primes = malloc(sizeof(int) * num_primes);

    // copy primes over to our new smaller array
    int integers_iterator = 0;
    int primes_iterator = 0;
    while (integers_iterator < LIMIT) {
        int prime = integers[integers_iterator];
        if (prime != 0)
        {
            primes[primes_iterator] = prime;
            primes_iterator++;
        }
        integers_iterator++;
    }

    free(integers);

    printf("printing primes...\n");
    printf("...\n");
    printf("...\n");
    printf("...\n");

    print_int_array(primes, num_primes);

    free(primes);

    return 0;
}

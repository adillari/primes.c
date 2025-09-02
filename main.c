#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define FILENAME "primes.txt"

void validate_args(int argc)
{
    if (argc != 2)
    {
        printf("Primes up to but not including {number}\n");
        printf("Usage: ./primes {number}\n");
        exit(1);
    }
}

uint64_t* allocate_integers_array(uint64_t size)
{
    uint64_t* integers = malloc(sizeof(uint64_t) * size);

    if (integers == NULL)
    {
        perror("malloc failed\n");
        exit(1);
    }

    return integers;
}

void fill_array_with_zero_to_limit(uint64_t* integers, uint64_t array_size)
{
    for (uint64_t index = 0; index < array_size; index++)
    {
        integers[index] = index;
    }
}

void replace_composites_with_zero(uint64_t* integers, uint64_t array_size)
{
    integers[1] = 0;

    for (uint64_t index = 2; index < array_size; index++)
    {
        // if (index > array_size/2) break;

        printf("filtering out multiples of %" PRIu64 "\n", index);

        uint64_t multiple = index;
        while (true)
        {
            multiple += index;

            if (multiple >= array_size) break;

            if (integers[multiple] == 0) continue;

            printf("setting %" PRIu64 " to 0\n", multiple);

            integers[index] = 0;
        }
    }
}

void save_primes_to_file(uint64_t* integers, uint64_t array_size)
{
    printf("\nSaving primes to %s...\n", FILENAME);

    FILE *fp = fopen(FILENAME, "w");

    if (fp == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    else
    {
        for (uint64_t index = 0; index < array_size; index++)
        {
            if (integers[index] == 0) continue;

            fprintf(fp, "%d\n", integers[index]);
        }
    }

    printf("\nSaved primes to %s...\n", FILENAME);
}


int main(int argc, char* argv[])
{
    validate_args(argc);

    const uint64_t LIMIT = strtoull(argv[1], NULL, 10);

    uint64_t* integers = allocate_integers_array(LIMIT);

    fill_array_with_zero_to_limit(integers, LIMIT);

    replace_composites_with_zero(integers, LIMIT);

    save_primes_to_file(integers, LIMIT);

    free(integers);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void validate_args(int argc)
{
    if (argc == 2) return;

    printf("Primes up to but not including {number}\n");
    printf("Usage: ./primes {number}\n");

    exit(1);
}

uint64_t* allocate_integers_array(uint64_t size)
{
    uint64_t* integers = malloc(sizeof(uint64_t) * size);

    if (integers) return integers;

    perror("malloc failed\n");

    exit(1);
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
        if (index > array_size/2) break;

        printf("Filtering out multiples of %" PRIu64 "\n", index);

        uint64_t multiple = index;

        while (true)
        {
            multiple += index;

            if (multiple >= array_size) break;

            if (integers[multiple] == 0) continue;

            printf("Setting %" PRIu64 " to 0\n", multiple);

            integers[multiple] = 0;
        }
    }
}

void save_primes_to_file(uint64_t* integers, uint64_t array_size, char* filename)
{
    printf("\nSaving primes to %s...\n", filename);

    FILE *fp = fopen(filename, "w");

    if (fp)
    {
        for (uint64_t index = 0; index < array_size; index++)
        {
            if (integers[index] == 0) continue;

            fprintf(fp, "%" PRIu64 "\n", integers[index]);
        }

        printf("\nSaved primes to %s...\n\n", filename);

        return;
    }

    perror("Error opening file");

    exit(1);
}

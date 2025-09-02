#include "sieve_functions.c"

#define FILENAME "primes.txt"

int main(int argc, char* argv[])
{
    validate_args(argc);

    const uint64_t LIMIT = strtoull(argv[1], NULL, 10);

    uint64_t* integers = allocate_integers_array(LIMIT);

    fill_array_with_zero_to_limit(integers, LIMIT);

    replace_composites_with_zero(integers, LIMIT);

    save_primes_to_file(integers, LIMIT, FILENAME);

    free(integers);

    return 0;
}

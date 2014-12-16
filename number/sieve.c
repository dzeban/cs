#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

void sieve(int n)
{
	int prime;
	int sieve_size;
	bool *s, *p;

	// We sieve only odd numbers starting from 3
	sieve_size = (n - 2) / 2;

	s = calloc(sieve_size, sizeof(bool));
	if (!s) {
		perror("malloc");
		return;
	}
	memset(s, false, sieve_size);

	printf("1\n");
	printf("2\n");

	for (int i = 0; i < sieve_size;)
	{
		// Current prime number.
		// Multiply by 2 because we skip even numbers.
		// Add 3 becasue we start with 3.
		prime = i * 2 + 3;

		printf("%d\n", prime);

		//Do sieve
		for (int j = i; j < sieve_size; j += prime)
		{
			s[j] = true;
		}

		// Move to next prime
		while (s[i] == true)
			i++;

		// Why this not working?
		// while (s[i++] == true);
	}

}

int main(int argc, const char *argv[])
{
	int n;

	if (argc != 2)
		return EXIT_FAILURE;
   
	n = strtol(argv[1], NULL, 0);

	if (n > LONG_MIN && n < LONG_MAX)
		sieve(n);

	return 0;
}

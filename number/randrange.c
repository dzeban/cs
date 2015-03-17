#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	unsigned int i = 0, j = 0, d = 0, n = 0;
	unsigned int seed = 0x16372789;
	long int r = 0;
	int is_binary = 0;
	int *distinct;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s [-b] <distinct elements> <number of ints>\n", argv[0]);
		fprintf(stderr, "with -b option output will be binary\n");
		return EXIT_FAILURE;
	}

	if (argc > 3) {
		if (!strncmp(argv[1], "-b", 3)) {
			is_binary = 1;

			// Pretend we didn't have that option ;-)
			argv++;
			argc--;
		}
	}

	errno = 0;
	d = strtol(argv[1], NULL, 0);
	if (errno) {
		perror("strtol");
		return EXIT_FAILURE;
	}

	errno = 0;
	n = strtol(argv[2], NULL, 0);
	if (errno) {
		perror("strtol");
		return EXIT_FAILURE;
	}

	if (is_binary)
		freopen(NULL, "wb", stdout);

	distinct = malloc(d * sizeof(int));
	if (!distinct) {
		perror("malloc");
		return EXIT_FAILURE;
	}

	srandom(seed);
	i = 0;
	j = d;
	while (j--)
	{
		// Despite random() return type is long int (size 8)
		// it always return 4 bytes randoms
		distinct[i++] = random();
	}

	while (n--)
	{
		r = distinct[random() % d];
		if (is_binary)
			fwrite(&r, sizeof(int), 1, stdout);
		else
			printf("%d\n", r);
	}

	free(distinct);
	
	return 0;
}

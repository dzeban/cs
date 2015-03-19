#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	int is_binary = 0;
	int range, n;
	int i, j;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s [-b] <range> <number of ints>\n", argv[0]);
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
	range = strtol(argv[1], NULL, 0);
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

	for (i = 0; i < range; i++)
	{
		for (j = 0; j < n/range; j++)
			printf("%d\n", i);
	}
	
	return 0;
}

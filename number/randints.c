#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	unsigned int i = 0;
	unsigned int n = 0;
	unsigned int seed = 0x16372789;

	if (argc < 2) 
	{
		fprintf(stderr, "Usage: %s <number of ints> [random seed]\n", argv[0]);
		return EXIT_FAILURE;
	}

	errno = 0;
	n = strtol(argv[1], NULL, 0);
	if (errno) 
	{
		perror("strtol");
		return EXIT_FAILURE;
	}

	if (argc == 3) 
	{
		errno = 0;
		seed = strtol(argv[2], NULL, 0);
		if (errno) 
		{
			perror("strtol");
			return EXIT_FAILURE;
		}
	}

	srandom(seed);
	while (n--) 
	{
		printf("%d\n", random());
	}
	
	return 0;
}

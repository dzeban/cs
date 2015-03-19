#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

void print_counter(int buf[], int range)
{
	int i, j;
	for (i = 0; i < range; i++)
		for(j = 0; j < buf[i]; j++)
			printf("%d\n", i);
}

int find_range(FILE *f, int bufn)
{
	int range = 0;
	int *buf;
	int read, i;

	buf = malloc(bufn * sizeof(int));
	if (!buf) {
		perror("malloc");
		return -1;
	}

	while (!feof(f))
	{
		read = fread(buf, sizeof(int), bufn, f);
		if (read == 0)
			break;

		for (i = 0; i < read; i++)
			if (buf[i] > range)
				range = buf[i];
	}

	// Range is from 0 to max inclusive
	range += 1;

	fprintf(stderr, "Range is %d\n", range);

	// Don't forget to rewind file
	fseek(f, 0, SEEK_SET);
	free(buf);
	return range; 
}

int counting_sort(FILE *f, int range, int bufn, int **pcounter)
{
	int *counter;
	int *buf;
	int read, i;

	counter = malloc(range * sizeof(int));
	if (!counter) {
		perror("malloc");
		return -1;
	}

	memset(counter, 0, range * sizeof(int));

	buf = malloc(bufn * sizeof(int));
	if (!buf) {
		perror("malloc");
		free(counter);
		return -1;
	}

	while (!feof(f))
	{
		read = fread(buf, sizeof(int), bufn, f);
		if (read == 0)
			break;

		for (i = 0; i < read; i++)
			counter[buf[i]]++;
	}

	*pcounter = counter;

	return 0;
}

int main(int argc, const char *argv[])
{
	FILE *f;
	off_t filesize;
	struct stat sb;
	clock_t start, end;
	int bufn = 100;
	int range = -1;
	int *counter;
	int rc;

	if (argc < 2) {
		fprintf(stderr, "%s <filename> [bufn] [range]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	f = fopen(argv[1], "rb");
	if (f == NULL) {
		fprintf(stderr, "Failed to open file %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	if (argc > 2) {
		bufn = strtol(argv[2], NULL, 0);
		if (argc == 4)
			range = strtol(argv[3], NULL, 0);
	}

	if (stat(argv[1], &sb)) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	filesize = sb.st_size;

	if (range < 0) {
		range = find_range(f, bufn);
		if (range < 0) {
			fprintf(stderr, "Failed to get range\n");
			exit(EXIT_FAILURE);
		}
	}

	start = clock();
	rc = counting_sort(f, range, bufn, &counter);
	end = clock();

	if (rc) {
		fprintf(stderr, "Failed to sort  %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	print_counter(counter, range);
	
	fprintf(stderr, "%ld bytes sorted in %f seconds\n", filesize, (double)(end - start) / CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}

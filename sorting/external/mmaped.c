/*
 * Sorting of big file with mmap.
 *
 * NOTE: This program works with files containing 
 * integers in raw binary form! Use raw_conv.py to 
 * convert from ASCII to raw binary and back.
 *
 * This program maps file to memory with mmap call and 
 * then invokes qsort on mmap'ed memory in hope that 
 * kernel will handle memory eviction and swapping by itself.
 *
 * Length of mapping can be supplied by user via 
 * command-line. By default, length of mapping is filesize.
 *
 * Copyright (c) 2015 Alex Dzyoba <avd@reduct.ru>
 * 
 * This project is licensed under the terms of the MIT license
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

void print_arr(int A[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d\n", A[i]);
}

int compar(const void *p1, const void *p2)
{
	int *i1, *i2;

	i1 = (int *)p1;
	i2 = (int *)p2;

	return *i1 - *i2;
}

int main(int argc, const char *argv[])
{
	int map_len;
	int fd;
	struct stat sb;
	int file_length;
	int *A;
	int n;
	clock_t start, end;

	if (argc < 2) {
		fprintf(stderr, "%s <filename> [<map len>]\n", argv[0]);
		return EXIT_FAILURE;
	}

	fd = open(argv[1], O_RDWR);
	if (fstat(fd, &sb) == -1) {
		perror("fstat");
		return EXIT_FAILURE;
	}

	file_length = sb.st_size;

	if (argc == 3) {
		map_len = strtol(argv[2], NULL, 0);
		if (errno) {
			perror("strtol");
			return EXIT_FAILURE;
		}
	} else {
		map_len = file_length;
	}

	A = mmap(NULL, map_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (A == MAP_FAILED) {
		perror("mmap");
		return EXIT_FAILURE;
	}

	n = file_length / sizeof(int); // Number of elements in file
	start = clock();
	qsort(A, n, sizeof(int), compar);
	end = clock();
	print_arr(A, n);
	
	fprintf(stderr, "%ld bytes sorted in %f seconds\n", file_length, (double)(end - start) / CLOCKS_PER_SEC); 
	return 0;
}

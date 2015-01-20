#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

void print_arr(int A[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d\n", A[i]);
	}
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

	n = file_length/sizeof(int);
	qsort(A, n, sizeof(int), compar);
	print_arr(A, n);
	
	return 0;
}

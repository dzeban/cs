#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct record {
	int n;
	int count;
};

struct bst {
	int n;
	int index;
	struct bst *left;
	struct bst *right;
};

// Count table 
struct CT {
	int size;
	struct record *table;
	struct bst *root; // Binary search tree for quick table index lookup
};

// Increasing coefficient used in dynamic resizing.
#define INC_COEFF 2

// Default hash table size
#define DEF_SIZE 10

struct CT *ct_new()
{
	struct CT *T = NULL;
	int n = 10;

	T = malloc(sizeof(*T));
	T->size = DEF_SIZE;
	T->table = calloc(T->size, sizeof(struct record));
	T->bst = NULL;

	return T;
}

void ct_del(struct CT *T)
{
	bst_free(T->root);
	free(T->table);
	free(T);
}

void ct_insert(struct CT *T, int d)
{
	
}

// Return number of elements
int counting_sort(FILE *f)
{
	int n, read;

	while (!feof(f))
	{
		read = fread(&d, sizeof(int), 1, f);
		if (read == 0)
			break;

		ct_insert(T, d);
	}

}

int main(int argc, const char *argv[])
{
	FILE *f;
	off_t filesize;
	struct stat sb;
	clock_t start, end;
	int n;

	if (argc < 2) {
		fprintf(stderr, "%s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}

	f = fopen(argv[1], "rb");
	if (f == NULL) {
		fprintf(stderr, "Failed to open file %s\n", filename);
		return EXIT_FAILURE;
	}

	// Check that buffer is aliquot part of file size.
	if (stat(argv[1], &sb)) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	filesize = sb.st_size;

	// XXX: Advise kernel about our read pattern
	posix_fadvise(fileno(f), 0, 0, POSIX_FADV_SEQUENTIAL);
	readahead(fileno(f), 0, filesize);

	start = clock();
	n = counting_sort(f);
	end = clock();

	fclose(f);

	fprintf(stderr, "%ld bytes sorted in %f seconds\n", n * sizeof(int), (double)(end - start) / CLOCKS_PER_SEC);
	
	return 0;
}

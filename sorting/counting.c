#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

struct counter {
	int n;
	int count;
};

struct bst {
	int n;
	int index;
	struct bst *left;
	struct bst *right;
};

// Counter table 
struct CT {
	int size;
	int last;
	struct counter *table;
	struct bst *root; // Binary search tree for quick table index lookup
};

// Increasing coefficient used in dynamic resizing.
#define INC_COEFF 10

// Default counter table size
#define DEF_SIZE 10

void bst_add(struct bst **root, int key, int val)
{
	if (*root) {
		if (key <= (*root)->n)
			bst_add(&((*root)->left), key, val);
		else
			bst_add(&((*root)->right), key, val);
	} else {
		struct bst *node = NULL;
		node = malloc(sizeof(*node));
		node->n = key;
		node->index = val;
		node->left = NULL;
		node->right = NULL;
		*root = node;
		return;
	}
}

struct bst *bst_find(struct bst *root, int key)
{
	// Base case: Not found
	if (root == NULL)
		return NULL;

	// Base case: Found
	if (root->n == key)
		return root;

	// Recurse on subtree
	if (key <= root->n)
		return bst_find(root->left, key);
	else
		return bst_find(root->right, key);
}

void bst_free(struct bst *root)
{
	if (root) {
		bst_free(root->left);
		bst_free(root->right);
		free(root);
	}
}

struct CT *ct_new()
{
	struct CT *T = NULL;
	int n = 10;

	T = malloc(sizeof(*T));
	T->size = DEF_SIZE;
	T->table = calloc(T->size, sizeof(struct counter));
	T->root = NULL;
	T->last = 0;

	return T;
}

void ct_free(struct CT *T)
{
	bst_free(T->root);
	free(T->table);
	free(T);
}

void ct_insert(struct CT *T, int d)
{
	int index = -1;
	struct bst *node = bst_find(T->root, d);

	// Counter exists - update it
	if (node) {
		index = node->index;
		T->table[index].count++;				
	} 
	// New element - add it
	else {
		index = T->last++;

		// Increase counter table size
		if (index == T->size) {
			// Do not multiply size. We must take care of memory consumption
			T->size += INC_COEFF;
			T->table = realloc(T->table, T->size * sizeof(struct counter));
		}

		T->table[index].n = d;		
		T->table[index].count = 1;
		bst_add(&(T->root), d, index);
	}
}

void ct_out(struct CT *T)
{
	int i;
	for (i = 0; i < T->size; i++)
	{
		int j;
		struct counter c = T->table[i];
		for (j = 0; j < c.count; j++)
			printf("%d\n", c.n);
	}
}

int counter_cmp(const void *p1, const void *p2)
{
	struct counter *c1, *c2;

	c1 = (struct counter *)p1;
	c2 = (struct counter *)p2;

	return (c1->n - c2->n);
}

// Return number of elements
int counting_sort(FILE *f, struct CT *T, size_t bufn)
{
	int d, read, i;
	int *buf;

	buf = malloc(bufn * sizeof(int));
	if (!buf) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (!feof(f))
	{
		read = fread(buf, sizeof(int), bufn, f);
		if (read == 0)
			break;

		for (i = 0; i < read; i++)
			ct_insert(T, buf[i]);
	}

	// Truncate counter table back
	T->table = realloc(T->table, T->last * sizeof(struct counter));
	T->size = T->last;

	// Now, we have table of counters, but we need to sort counters.
	// Assuming range is much smaller than data, it's going to be fast.
	qsort(T->table, T->last, sizeof(struct counter), counter_cmp);

	free(buf);

	return T->last;
}

int main(int argc, const char *argv[])
{
	FILE *f;
	off_t filesize;
	struct stat sb;
	struct CT *T;
	clock_t start, end;
	int n;
	size_t bufn = 100;

	if (argc < 2) {
		fprintf(stderr, "%s <filename> [buffer elements=100]\n", argv[0]);
		return EXIT_FAILURE;
	}

	f = fopen(argv[1], "rb");
	if (f == NULL) {
		fprintf(stderr, "Failed to open file %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	if (argc == 3)
		bufn = strtol(argv[2], NULL, 0);

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
	T = ct_new();
	n = counting_sort(f, T, bufn);
	end = clock();

	ct_out(T);
	ct_free(T);

	fclose(f);

	fprintf(stderr, "%ld bytes sorted in %f seconds\n", filesize, (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}

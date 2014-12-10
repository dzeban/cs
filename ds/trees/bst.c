#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../queue/queue_void.h"

#define max(a, b) a > b ? a : b

struct bst {
	int n;
	struct bst *left;
	struct bst *right;
};

int bst_add(struct bst **tree, int n)
{
	if (*tree) 
	{
		// Find the place to insert
		if (n <= (*tree)->n)
			bst_add(&((*tree)->left), n);
		else 
			bst_add(&((*tree)->right), n);
	} 
	else 
	{
		struct bst *node = NULL;
		node = malloc(sizeof(*node));
		if (!node)
			return -1;

		node->n = n;
		node->left = NULL;
		node->right = NULL;
		*tree = node;
		return 0;
	}
}

void bst_in_order(struct bst *tree)
{
	if (tree) {
		bst_in_order(tree->left);
		printf("%d\n", tree->n);
		bst_in_order(tree->right);
	}
}

void bst_pre_order(struct bst *tree)
{
	if (tree) {
		printf("%d\n", tree->n);
		bst_pre_order(tree->left);
		bst_pre_order(tree->right);
	}
}

void bst_post_order(struct bst *tree)
{
	if (tree) {
		bst_post_order(tree->left);
		bst_post_order(tree->right);
		printf("%d\n", tree->n);
	}
}

void bst_level_order(struct bst *tree)
{
	struct queue *q;
	struct bst *node;

	q = queue_init();
	enq(q, (void *)tree);

	while (deq(q, (void **)(&node)) == 0)
	{
		if (!node) continue;

		printf("%d\n", node->n);
		enq(q, node->left);
		enq(q, node->right);
	}
}

void bst_free(struct bst *tree)
{
	if (tree) {
		bst_free(tree->left);
		bst_free(tree->right);
		free(tree);
	}
}

int bst_height(struct bst *tree)
{
	// Base case
	if (tree == NULL) {
		return 0;
	}
	// Generic case: height is max of subtrees + 1
	else {
		int l, r, m;
		l = bst_height(tree->left);
		r = bst_height(tree->right);
		m = max(l, r);

		return 1 + m;
	}
}

bool bst_check_balanced(struct bst *tree)
{
	int l, r;
	if (tree == NULL)
		return true;

	l = bst_height(tree->left);
	r = bst_height(tree->right);

	if (abs(l - r) > 1) 
		return false;

	return bst_check_balanced(tree->left) && bst_check_balanced(tree->right);
}

int bst_check_height(struct bst *tree)
{
	if (tree == NULL) {
		return 0;
	} else {
		int l, r, m;
		l = bst_height(tree->left);
		if (l == -1)
			return -1;

		r = bst_height(tree->right);
		if (r == -1)
			return -1;

		m = max(l, r);

		if (abs(l-r) > 1)
			return -1;
		else
			return 1 + m;
	}
}

bool bst_check_balanced_optimized(struct bst *tree)
{
	if (bst_check_height(tree) == -1)
		return false;
	else
		return true;
}

int main(int argc, const char *argv[])
{
	int N, n, i;
	struct bst *root;

	N = argc - 1;
	if (N < 1)
		return -1;

	root = NULL;
	argv++;
	for (i = 0; i < N; i++) 
	{
		n = strtol(argv[i], NULL, 0);
		bst_add(&root, n);
	}

	printf("Height: %d\n", bst_height(root));
	printf("Balanced: %d\n", bst_check_balanced_optimized(root));

	bst_in_order(root);
	printf("----\n");
	bst_pre_order(root);
	printf("----\n");
	bst_post_order(root);
	printf("----\n");
	bst_level_order(root);
	printf("----\n");
	
	bst_free(root);
	return 0;
}

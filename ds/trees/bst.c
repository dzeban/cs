#include <stdio.h>
#include <stdlib.h>

#include "../queue/queue_void.h"

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

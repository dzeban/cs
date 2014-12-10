#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main(int argc, const char *argv[])
{
	int N, n, i;
	struct queue *q;

	N = argc - 1;
	if (N < 1) return -1;


	q = queue_init();

	argv++;
	for (i = 0; i < N; i++)
	{
		n = strtol(argv[i], NULL, 0);
		enq(q, n);
	}

	queue_print(q);

	for (i = 0; i < N - 1; i++)
	{
		n = strtol(argv[i], NULL, 0);
		deq(q, &n);
		queue_print(q);
	}
	

	queue_free(q);

	return 0;
}

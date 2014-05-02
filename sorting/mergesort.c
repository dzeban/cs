#include <stdio.h>
#include <stdlib.h>

void print_array(int *array, int length)
{
	int i;
	for(i = 0; i < length; i++)
		printf("%d ", array[i]);
	printf("\n");
}

void merge(int *array, int *left, int left_len, int *right, int right_len)
{
	int i, j, k;

	i = j = k = 0;
	while (i < left_len && j < right_len)
	{
		if (left[i] <= right[j])
			array[k++] = left[i++];
		else
			array[k++] = right[j++];
	}

	// Copy leftovers
	while (i < left_len)
		array[k++] = left[i++];
	
	while (j < right_len)
		array[k++] = right[j++];
}

void mergesort(int *array, int length)
{
	int left_len  = length/2;
	int right_len = length - length/2;

	int left[left_len];
	int right[right_len];

	int i, j, k;
	
	// Recursion base
	if (length == 1)
		return;

	i = j = k = 0;

	// Copy halves
	while (i < left_len)
		left[i++] = array[k++];
	
	while (j < right_len)
		right[j++] = array[k++];

	mergesort(left, left_len);
	mergesort(right, right_len);
	merge(array, left, left_len, right, right_len);
}

int main(int argc, char *argv[])
{
	int i = 0;
	int length = argc - 1;
	int *array = malloc(sizeof(int) * length);

	argv++; // Start with first argument
	while( i < length )
	{
		array[i++] = atoi(*(argv++));
	}
	printf("Original:\n");
	print_array(array, length);

	mergesort(array, length);

	printf("Sorted:\n");
	print_array(array, length);

	free(array);

	return 0;
}

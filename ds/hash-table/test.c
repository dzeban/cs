#include <stdio.h>
#include <stdlib.h>

#include "hash-table.h"

#define N 3

int main(int argc, const char *argv[])
{
	struct hash_table *ht = NULL;

	if (hash_table_create(&ht, N))
	{
		perror("hash_table_create");
		exit(EXIT_FAILURE);
	}

	hash_table_print(ht);

	hash_table_insert(ht, "abc");
	hash_table_insert(ht, "oh");
	hash_table_insert(ht, "my");
	hash_table_insert(ht, "god");
	hash_table_insert(ht, "onotole");
	hash_table_insert(ht, "odinodin");
	hash_table_insert(ht, "getcha");
	hash_table_insert(ht, "kotenka");
	hash_table_insert(ht, "kisulenka");

	hash_table_print(ht);

	printf("abc: %s\n", hash_table_get(ht, "abc"));
	printf("my: %s\n", hash_table_get(ht, "my"));

	hash_table_remove(ht, "getcha");

	hash_table_print(ht);

	hash_table_destroy(ht);
	
	return 0;
}

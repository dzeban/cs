#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "hash-table.h"

#define HASH_PRIME 31

static int simple_hash(char *s, int table_size) 
{
	int hash = 0;
	int len = 0;
	int i = 0;

	if (!s)
		return -EINVAL;

	len = strlen(s);
	if (len < 1)
		return -EINVAL;

	for (i = 0; i < len; i++)
		hash = (HASH_PRIME * hash + s[i]) % table_size;
   
	return hash;
}

int hash_table_create(struct hash_table **user_hash_table, int size)
{
	int ret = 0;
	int i = 0;
	struct hash_table *HT = NULL;

	HT = malloc(sizeof(*HT));
	if (!HT) 
	{
		perror("malloc");
		ret = -ENOMEM;
		goto err;
	}

	HT->table = malloc(sizeof(struct bucket) * size);
	if (!HT->table)
	{
		perror("malloc");
		return -ENOMEM;
	}

	for (i = 0; i < size; i++)
		HT->table[i] = NULL;

	HT->size = size;

	*user_hash_table = HT;
	return 0;

err:
	if (HT->table)
		free(HT->table);

	if (HT)
		free(HT);

	return ret;

}

void hash_table_destroy(struct hash_table *HT)
{
	int i = 0;

	for (i = 0; i < HT->size; i++)
	{
		struct bucket *b, *next;

	    b = HT->table[i];
		while (b)
		{
			next = b->next;
			free(b);
			b = next;
		}
	}

	free(HT->table);
	free(HT);
}

void hash_table_print(struct hash_table *HT)
{
	int i = 0;

	printf("-----------------------------\n");
	printf("Hash table at %p:\n\n", HT);
	
	for (i = 0; i < HT->size; i++)
	{
		if (HT->table[i])
		{
			struct bucket *b;

			printf("%d: ", i);

			b = HT->table[i];
			while (b)
			{
				printf("%s -> ", b->value);
				b = b->next;
			}
			printf("0\n");
		}
	}

	printf("-----------------------------\n");
}

int hash_table_insert(struct hash_table *HT, char *value)
{
	int hash = -1;
	struct bucket *new_bucket = NULL;

	hash = simple_hash(value, HT->size);
	if (hash < 0)
		return -EINVAL;

	if (hash_table_get(HT, value))
		return -EEXIST;

	new_bucket = malloc(sizeof(*new_bucket));
	new_bucket->value = strdup(value);
	new_bucket->next  = NULL;

	if (HT->table[hash] == NULL)
	{
		HT->table[hash] = new_bucket;
	}
	else
	{
		struct bucket *b = HT->table[hash];
		while (b->next)
			b = b->next;

		b->next = new_bucket;
	}

	return 0;
}

char *hash_table_get(struct hash_table *HT, char *value)
{
	int hash = -1;
	
	hash = simple_hash(value, HT->size);
	if (hash < 0)
		return NULL;

	if (HT->table[hash] != NULL)
	{
		int len = strlen(value);
		struct bucket *b = HT->table[hash];
		while (b)
		{
			if (!strncmp(b->value, value, len))
				return b->value;

			b = b->next;
		}
	}

	return NULL;
}

int hash_table_remove(struct hash_table *HT, char *value)
{
	int hash = -1;
	int len = 0;
	
	hash = simple_hash(value, HT->size);
	if (hash < 0)
		return -EINVAL;

	len = strlen(value);

	if (HT->table[hash])
	{
		struct bucket *del;
		struct bucket **pp;

		pp = &(HT->table[hash]);
		while(*pp)
		{
			if (!strncmp((*pp)->value, value, len))
			{
				del = *pp;
				*pp = (*pp)->next;
				free(del);
				return 0;
			}

			pp = &((*pp)->next);
		}
	}

	return -ESRCH;
}



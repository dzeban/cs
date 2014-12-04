#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

struct bucket {
	char *value;
	struct bucket *next;
};

struct hash_table {
	int size;
	struct bucket **table;
};

int   hash_table_create(struct hash_table **HT, int n);
void  hash_table_destroy(struct hash_table *HT);

int   hash_table_insert(struct hash_table *HT, char *value);
char *hash_table_get(struct hash_table *HT, char *value);
int   hash_table_remove(struct hash_table *HT, char *value);

#endif // __HASH_TABLE_H

#if !defined(_HASH_H_)
#define _HASH_H_

#include "new.h"
#include "list_in_ht.h"
#include "object.h"

typedef void *Pointer;
typedef unsigned(*HashFunction)(char *key);

struct HashTable
{
	const void *TypeDescriptor;
	size_t size;
	struct List **table;
	HashFunction hf;
};


Pointer ht_get(Pointer _self, char *key);

Pointer ht_resize(Pointer _self, size_t new_size, size_t SizeData);

unsigned jenkins_one_at_a_time_hash(char *key);

Pointer ht_set(Pointer _self, char *key, Pointer data, size_t SizeData);

int ht_has(Pointer _self, char *key);

Pointer ht_delete(Pointer _self, char* key);

Pointer ht_traverse(Pointer _self, void(*f)(char *key, Pointer data));

Pointer ht_resize(Pointer _self, size_t new_size);

extern const void *HashTable;

#endif
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "HashTable_ooc.h" 
#include "new.h"
#include "object.h"
#include "list_in_ht.h"


unsigned jenkins_one_at_a_time_hash(char *key) {
	unsigned hash = 0;

	for (; *key; ++key) {
		hash += *key;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

static Pointer ht_init(Pointer _self, va_list *app)
{
	struct HashTable* self = _self;
	HashFunction hf = NULL;

	self->size = va_arg(*app, size_t);
	self->table = (struct List**)calloc(self->size, sizeof(struct List*));

	hf = va_arg(*app, HashFunction);
	if (hf != NULL)
	{
		self->hf = hf;
	}
	else
	{
		self->hf = jenkins_one_at_a_time_hash;
	}
	return self;
}

void* ht_destroy(Pointer *_self)
{
	struct HashTable* self = _self;
	int i;
	
	for (i = 0; i<self->size; i++)
	{
		delete(self->table[i]);
	}
	
	free(self->table);
	free(self);
}

Pointer ht_set(Pointer _self, char *key, Pointer data, size_t sizedata)
{
	struct HashTable* self = _self;
	struct List* newlist;
	struct List * buf;
	unsigned index;
	int ddd;

	index = self->hf(key) % self->size;
	buf = self->table[index];
	while (buf != NULL)
	{
		if (strcmp(buf->key, key) == 0)
		{
			delete(buf->data);
			buf->data = (struct Object*)data;
			return self;
		}
		buf = buf->next;
	}
	self->table[index] = list_prepend(self->table[index], key, data, sizedata);
	return self;
}

Pointer ht_get(Pointer _self, char *key)
{
	struct HashTable* self = _self;
	size_t index;
	struct List * buf;
	index = self->hf(key) % self->size;
	buf = self->table[index];
	while (buf != NULL)
	{
		if (strcmp(buf->key, key) == 0)
		{
			return buf->data;
		}
		buf = buf->next;
	}
	return NULL;
}

int ht_has(Pointer _self, char *key)
{
	struct HashTable* self = _self;
	size_t index;
	struct List * buf;
	index = self->hf(key) % self->size;
	buf = self->table[index];
	if (list_has(buf, key) == 1)
	{
		return 1;
	}
	return 0;
}

Pointer ht_delete(Pointer _self, char* key)
{
	struct HashTable* self = _self;
	size_t index;
	index = self->hf(key) % self->size;
	if (!self->table[index])
	{
		return self;
	}
	self->table[index] = list_remove_all(self->table[index], key);
	return self;
}

Pointer ht_traverse(Pointer _self, void(*f)(char *key, Pointer data))
{
	struct HashTable* self = _self;
	size_t i;
	struct List * buf;
	for (i = 0; i<self->size; i++)
	{
		buf = self->table[i];
		list_foreach(buf, f);
	}
	return self;
}

Pointer ht_resize(Pointer _self, size_t new_size)
{
	struct HashTable* self = _self;
	struct List ** new_table;
	struct List * buf;
	size_t i;
	size_t index;
	new_table = (struct List**)calloc(new_size, sizeof(struct List*));
	for (i = 0; i<self->size; i++)
	{
		buf = self->table[i];
		while (buf != 0)
		{
			index = self->hf(buf->key) % new_size;
			new_table[index] = (struct List*) list_prepend(new_table[index], buf->key, buf->data, buf->size);
			buf = buf->next;
		}
		delete(self->table[i]);
	}
	free(self->table);
	self->table = new_table;
	self->size = new_size;
	return self;
}

static const struct TypeDescriptor _HashTable = {
	sizeof(struct HashTable),
	ht_init,
	ht_destroy
};

const void *HashTable = &_HashTable;


#ifndef HASHTABLE_R
#define HASHTABLE_R

#include "Object_r.h"

typedef struct HashTable HASHTABLE;
typedef struct HashTableClass HASHTABLE_CLASS;

typedef unsigned(*HashFunction)(char *key);

struct HashTable
{
	const OBJECT _;

	size_t size;
	struct List **table;
	HashFunction hf;
};

struct HashTableClass
{
	const OBJECT_CLASS _;

	void(*pfnDraw) (const void * _pSelf);
};

extern void base_draw(const void * _pClass, const void * _pSelf);

#endif
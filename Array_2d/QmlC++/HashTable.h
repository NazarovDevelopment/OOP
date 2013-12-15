#pragma once

#include "List.h"

typedef unsigned(*HashFunction)(char *key);


class HashTable
{
public:
	HashTable(size_t ArraySize);
	HashTable(size_t ArraySize, HashFunction hfunc);
	~HashTable();
	
private:
	List** table;
	size_t size;
	HashFunction hf;

};

HashTable::HashTable(size_t ArraySize)
{
	size = ArraySize;

	table = new List*[size];//(struct List**)calloc(pSelf->size, sizeof(struct List*));

	hf = ;
	
}


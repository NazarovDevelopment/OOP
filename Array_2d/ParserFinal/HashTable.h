#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "List.h"

typedef unsigned(*HashFunction)(char *key);


class HashTable
{
public:
	HashTable(size_t ArraySize);
	HashTable(size_t ArraySize, HashFunction hfunc);
	~HashTable();

public:

	void set(char* Putkey, void* Putvalue, int size);
	void* get(char* Putkey);
	bool has(char* Putkey);
	void traverse(void(*f)(char *key, void* data));
	void resize(int new_size);
	
private:

	List** table;
	size_t hashsize;
	HashFunction hf;

};

#endif
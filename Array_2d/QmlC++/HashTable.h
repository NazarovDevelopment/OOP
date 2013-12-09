#pragma once
typedef unsigned(*HashFunction)(char *key);

class HashTable
{
public:
	HashTable();
	HashTable(size_t ArraySize);
	HashTable(size_t ArraySize, HashFunction hfunc);
	~HashTable();
	
private:
	void** table;
	size_t size;
	HashFunction hf;

};
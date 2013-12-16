#pragma once

#include "List.h"

typedef unsigned(*HashFunction)(char *key);


class HashTable
{
public:
	HashTable(size_t ArraySize);
	HashTable(size_t ArraySize, HashFunction hfunc);
	~HashTable();

public:

	void set(char* Putkey, void* Putvalue);
	void* get(char* Putkey);
	bool has(char* Putkey);
	void traverse(void(*f)(char *key, void* data));
	void resize(int new_size);
	
private:

	List** table;
	size_t size;
	HashFunction hf;

};

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

HashTable::HashTable(size_t ArraySize)
{
	size = ArraySize;

	table = new List*[size];//(struct List**)calloc(pSelf->size, sizeof(struct List*));
	hf = jenkins_one_at_a_time_hash;
	
	for (int i = 0; i < size; i++)
	{
		table[i] = NULL;
	}
}

HashTable::HashTable(size_t ArraySize, HashFunction hfunc)
{
	size = ArraySize;

	table = new List*[size];//(struct List**)calloc(pSelf->size, sizeof(struct List*));
	hf = hfunc;

	for (int i = 0; i < size; i++)
	{
		table[i] = NULL;
	}
}

HashTable::~HashTable()
{
	for (int i = 0; i < size; i++)
	{
		delete(table[i]);
	}

	delete(table);
}

void HashTable::set(char* Putkey, void* Putvalue)
{
	int index = hf(Putkey) % size;
	List* buffer = table[index];

	while (buffer != NULL)
	{
		if (strcmp(buffer->Getkey(), Putkey) == 0)
		{
			delete(buffer->data);
			buffer->SetData(Putvalue);
			return;
		}
		buffer = buffer->next;
	}
	List* new_list = new List(Putkey, Putvalue);
	new_list->next = table[index];
	table[index] = new_list;
	//table[index] = table[index]->prepend(Putkey, Putvalue);
}

void* HashTable::get(char* Putkey)
{
	int index = hf(Putkey) % size;
	List* buf = table[index];
	while (buf != NULL)
	{
		if (strcmp(buf->Getkey(), Putkey) == 0)
		{
			return buf->data->GetValue();
		}
		buf = buf->next;
	}
	return NULL;
}

bool HashTable::has(char* Putkey)
{
	int index = hf(Putkey) % size;
	List* buf = table[index];
	if (table[index]->has(Putkey) == 1)
	{
		return 1;
	}
	return 0;
}

void HashTable::traverse(void(*f)(char *Putkey, void* Putvalue))
{
	List* buf;
	for (int i = 0; i<size; i++)
	{
		buf = table[i];
		buf->foreach(f);
	}
}

void HashTable::resize(int new_size)
{
	List** new_table = table;
	int old_size = size;
	size = new_size;
	
	table = new List*[new_size];
	for (int i = 0; i < new_size; i++)
	{
		table[i] = NULL;
	}

	for (int i = 0; i < old_size; i++)
	{
		List* testlist = new_table[i];
		while (testlist)
		{
			this->set(testlist->Getkey(), testlist->data->GetValue());
			testlist = testlist->next;
		}
	}
	size = new_size;

	for (int i = 0; i < old_size; i++)
	{
		delete(new_table[i]);
	}
	delete(new_table);
}
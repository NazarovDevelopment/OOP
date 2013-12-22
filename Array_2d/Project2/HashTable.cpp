#include "HashTable.h"


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
	hashsize = ArraySize;

	table = new List*[hashsize];//(struct List**)calloc(pSelf->size, sizeof(struct List*));
	hf = jenkins_one_at_a_time_hash;

	for (int i = 0; i < hashsize; i++)
	{
		table[i] = NULL;
	}
}

HashTable::HashTable(size_t ArraySize, HashFunction hfunc)
{
	hashsize = ArraySize;

	table = new List*[hashsize];//(struct List**)calloc(pSelf->size, sizeof(struct List*));
	hf = hfunc;
	if (hf == NULL)
	{
		hf = jenkins_one_at_a_time_hash;
	}

	for (int i = 0; i < hashsize; i++)
	{
		table[i] = NULL;
	}
}

HashTable::~HashTable()
{
	for (int i = 0; i < hashsize; i++)
	{
		delete(table[i]);
	}

	delete(table);
}
/*
void* HashTable::get(char* Putkey)
{
	int index = hf(Putkey) % hashsize;
	List* buf = table[index];
	while (buf != NULL)
	{
		if (strcmp(buf->Getkey(), Putkey) == 0)
		{
			return  buf->data->GetValue();
		}
		buf = buf->next;
	}
	return NULL;
}
*/
bool HashTable::has(char* Putkey)
{
	int index = hf(Putkey) % hashsize;
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
	for (int i = 0; i<hashsize; i++)
	{
		buf = table[i];
		buf->foreach(f);
	}
}

//void HashTable::resize(int new_size)
//{
//	List** new_table = table;
//	int old_size = hashsize;
//	hashsize = new_size;
//
//	table = new List*[new_size];
//	for (int i = 0; i < new_size; i++)
//	{
//		table[i] = NULL;
//	}
//
//	for (int i = 0; i < old_size; i++)
//	{
//		List* testlist = new_table[i];
//		while (testlist)
//		{
//			this->set(testlist->Getkey(), testlist->data->GetValue());
//			testlist = testlist->next;
//		}
//	}
//	hashsize = new_size;
//
//	for (int i = 0; i < old_size; i++)
//	{
//		delete(new_table[i]);
//	}
//	delete(new_table);
//}
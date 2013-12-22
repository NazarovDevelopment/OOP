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

	void set(char* Putkey, const int &Putvalue)
	{
		int index = hf(Putkey) % hashsize;
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
	}
	void set(char* Putkey, const std::string &Putvalue)
	{
		int index = hf(Putkey) % hashsize;
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
	}

	
	template<typename _T>
	_T get(char* Putkey) {
		int index = hf(Putkey) % hashsize;
		List* buf = table[index];
		while (buf != NULL)
		{
			if (strcmp(buf->Getkey(), Putkey) == 0)
			{
				IDataWrapper &wrapper = *buf->data->GetValue();
				return  (_T) wrapper;
			}
			buf = buf->next;
		}
		return NULL;
	}


	bool has(char* Putkey);
	
	void traverse(void(*f)(char *key, void* data));

	//void resize(int new_size);
	
private:

	List** table;
	size_t hashsize;
	HashFunction hf;

};

#endif
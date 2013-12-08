
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

//---------------------------------------------------------------------------------
List* slist_prepend(List *list, Pointer data, char* key)
{
	List* newlist;

    newlist = (List*) malloc(sizeof(List));
    newlist->key  = key;
    newlist->data = data;
    newlist->next = NULL;
    return newlist;
}
void slist_foreach(List *list, void (*f)(char *key, Pointer data))
{
	while(list != NULL)
	{
		f(list->key, list->data);
		list = list->next;
	}
}
List *slist_remove_all(List *list, char* key, Destructor dtor)
{
	List* curlist;
	List* buflist;
	curlist = list;
	/////////////////////////////////////////////////////
	if(dtor)
	{
		while(!strcmp(curlist->key, key))
		{
			curlist = curlist->next;
			dtor(curlist->data);
			free(list);
			list=curlist;
			if(list==NULL)
			{
				return list;
			}
		}
		//-------------------------------
		while(curlist->next)
		{
			while(!strcmp(curlist->key, key))
			{
				curlist = curlist->next;
				dtor(curlist->data);
				free(list);
				list = curlist;
				if(list == NULL)
				{
					return list;
				}
			}

			if(curlist->next == NULL)
			{
				return list;
			}

			if(!strcmp(curlist->next->key, key))
			{

				buflist = curlist->next;
				curlist->next = curlist->next->next;
				dtor(buflist->data);
				free(buflist);
			}

			if(curlist->next == NULL)
			{
				return list;
			}
			curlist = curlist->next;
		}
	}
	else
	{
		while(!strcmp(curlist->key, key))
		{
			curlist = curlist->next;
			free(list);
			list = curlist;
			if(list == NULL)
			{
				return list;
			}
		}

		while(curlist->next)
		{
			while(!strcmp(curlist->key, key))
			{
				curlist = curlist->next;
				free(list);
				list = curlist;
				if(list == NULL)
				{
					return list;
				}
			}
			if(curlist->next == NULL)
			{
				return list;
			}
			if(!strcmp(curlist->next->key, key))
			{
				buflist = curlist->next;
				curlist->next = curlist->next->next;
				free(buflist);
			}
			if(curlist->next == NULL)
			{
				return list;
			}
			curlist = curlist->next;
		}
	}
	return list;
}
void slist_destroy(List* list)
{
	List *buf;
	List* buf2;

	buf2 = buf = list;
	while (buf->next != NULL)
	{
		buf2 = buf->next;
		free(buf);
		buf = buf2;
	}
}
//---------------------------------------------------------------------------------
HashTable* ht_init(size_t size, HashFunction hf, Destructor dtor)
{
	HashTable *ht;
	size_t i;
        ht = (HashTable*)malloc(sizeof(HashTable));
        ht->table = (List**)malloc(sizeof(List)*size);
        ht->size = size;

        if(hf != NULL){
                ht->hashfunc = hf;
        }else{
                 ht->hashfunc = jenkins_one_at_a_time_hash;
        }

        if(dtor != NULL){
            ht->dtor = dtor;
        }else{
            ht->dtor = NULL;
        }

        for(i = 0; i < ht->size; i++){
            ht->table[i] = NULL;
        }
		return ht;
}
void ht_destroy(HashTable *ht)
{
	int i;
	if(ht->dtor == NULL)
	{
		for(i = 0; i<ht->size; i++)
		{
			free(ht->table[i]);
		}
	}
	else
	{
		for(i = 0; i < ht->size; i++)
		{
			ht->dtor(ht->table[i]->data);
			free(ht->table[i]);
		}
	}
	//-----------
	free(ht->table);
	free(ht);
}
void ht_set(HashTable *ht, char *key, Pointer data)
{
	unsigned ind;
	List *buffer;

	ind = ht->hashfunc(key) %  ht->size;
	buffer = ht->table[ind];

	/*if(ht->dtor == NULL)
	{*/
		while(buffer != NULL)
		{
			if (strcmp(buffer->key, key) == 0)
			{
				buffer->data = data;
				return;
			}
			buffer = buffer->next;
		}
	/*}else{
		while(buffer != NULL)
		{
			if (strcmp(buffer->key, key) == 0)
			{
				ht->dtor(buffer->data);
				buffer->data = data;
				return;
			}
			buffer = buffer->next;
		}
	} */
		ht->table[ind] = slist_prepend(ht->table[ind], data, key);

		printf("%s", ht->table[ind]->key);
}
Pointer ht_get(HashTable *ht, char *key)
{
        size_t ind;
        List * buffer;

        ind    = ht->hashfunc(key) % ht->size;
        buffer = ht->table[ind];
        
		while(buffer != NULL)
        {
                if(strcmp(buffer->key, key) == 0)
                {
                        return buffer->data;
                }
                buffer = buffer->next;
        }
        return NULL;
}
int ht_has(HashTable *ht, char *key)
{
        size_t ind;
        List * buffer;

        ind    = ht->hashfunc(key) % ht->size;
        buffer = ht->table[ind];

        while(buffer != NULL)
        {
			if(strcmp(buffer->key, key)==0)
            {
				return 1;
			}
			buffer = buffer->next;
        }
        return 0;
}
void ht_delete(HashTable *ht, char *key)
{
       /* size_t ind;
        List * buffer;
        List * buffer2;

        ind    = ht->hashfunc(key) % ht->size;
		buffer2 = buffer = ht->table[ind];

        if(buffer == NULL) 
        {
			printf("buffer is empty");        
			return;
        }

        while(buffer->next != NULL)
        {                
                if(strcmp(buffer->key, key) == 0)
                {
					if(ht->dtor != NULL)
                    {
						ht->dtor(buffer->data);            
						buffer2->next = buffer->next;
						free(buffer);
                        return;
                    }
                    else
					{
						buffer2->next = buffer->next;
                        free(buffer);
                        return;
                    }
                }
				buffer2 = buffer;
                buffer = buffer->next;
        }

        buffer2 = buffer;

        if(strcmp(buffer->key, key) == 0)
        {
			if(ht->dtor!=NULL)
            {
				ht->dtor(buffer->data);
			    buffer2->next=buffer->next;
                free(buffer);
				buffer = NULL;
                return;
			}
			else
            {
				buffer2->next = buffer->next;
                free(buffer);
				buffer = NULL;
                return;
            }
        }*/

	size_t index;
	List * buf;
	List * buflist;
	index = ht->hashfunc(key) % ht->size;
	if(!ht->table[index]) 
	{
		return;
	}
	ht->table[index] = slist_remove_all(ht->table[index], key, ht->dtor);
	return;
}

void ht_traverse(HashTable *ht, void (*f)(char *key, Pointer data))
{
        size_t i;
        List * buffer;

        for(i = 0; i < ht->size; i++)
        {
                buffer = ht->table[i];
                slist_foreach(buffer, f);
        }
}
void ht_resize(HashTable *ht, size_t new_size)
{
        List ** new_table;
        List * buffer;
        size_t i;
        size_t ind;

        new_table = (List**) malloc(sizeof(List)*new_size);

        for(i = 0; i < ht->size; i++)
        {
			buffer = ht->table[i];
            while(buffer != 0)
            {
				ind = ht->hashfunc(buffer->key) % new_size;
                slist_prepend(new_table[ind], buffer->data, buffer->key);
                buffer = buffer->next;
            }
            free(ht->table[i]);
        }
        
		free(ht->table);
        ht->table = new_table;
        ht->size = new_size;
}
//-----------------------------------------------------------------------------
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
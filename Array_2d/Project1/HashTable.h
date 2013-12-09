#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Object.h"

extern const void * HashTable;      
extern const void * HashTableClass; 


void draw(const void * _pSelf);

void* HashTable_dtor(void* _self);
void init_HashTableClass(void);

void* ht_get(void* _self, char *key);

void* ht_resize(void* _self, size_t new_size);

unsigned jenkins_one_at_a_time_hash(char *key);

void* ht_set(void* _self, char *key, void* data, size_t sizedata);

int ht_has(void* _self, char *key);

void* ht_delete(void* _self, char* key);

void* ht_traverse(void* _self, void(*f)(char *key, void* data));

void* ht_resize(void* _self, size_t new_size);


#endif
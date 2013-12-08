
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Object.h"

extern const void * HashTable;      
extern const void * HashTableClass; 


void draw(const void * _pSelf);

void* HashTable_dtor(void* _self);
void init_HashTableClass(void);

#endif
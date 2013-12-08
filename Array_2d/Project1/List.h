#ifndef LIST_H
#define LIST_H

#include "Object.h"

extern const void * List;
extern const void * ListClass;

extern void draw(const void* _pSelf);

void* List_dtor(void *_pSelf);

void* list_prepend(void* _list, char* key, void* data, size_t sizedata);

void* list_foreach(void* _list, void(*f)(char *key, void* data));

int list_has(void* _list, char* key);

void* list_remove_all(void* _list, char* key);

void list_delete_one(void* _self);

void init_ListClass(void);

#endif
#if !defined(_LIST_H_)
#define _LIST_H_

#include "new.h"
#include "object.h"

typedef void* Pointer;

struct List
{
	const void *class;
	char *key;
	struct Object* data;
	struct List *next;
};

Pointer list_prepend(Pointer _list, char* key, Pointer data);

Pointer list_foreach(Pointer _list, void(*f)(char *key, Pointer data));

int list_has(Pointer _list, char* key);

Pointer list_remove_all(Pointer _list, char* key);

void list_delete_one(Pointer _self);

extern const void *List;

#endif
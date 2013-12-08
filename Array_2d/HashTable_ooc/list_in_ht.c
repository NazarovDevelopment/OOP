#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "list_in_ht.h"
#include "object.h"
#include "new.h"
#pragma warning(disable : 4996)



static Pointer list_create(Pointer _self, va_list* app)
{
	char* keykey;
	struct List* self = _self;
	self->next = NULL;
	self->data = va_arg(*app, void*);
	keykey = va_arg(*app, char*);
	self->key = (char*)malloc(sizeof(keykey));
	self->key = (self->key, keykey);
	return self;
}

Pointer list_remove_all(Pointer _list, char* key)
{
	struct List* list = _list;
	struct List* curlist;
	struct List* buflist;
	curlist = list;
	while (!strcmp(curlist->key, key))
	{
		curlist = curlist->next;
		list_delete_one(list);
		list = curlist;
		if (list == NULL)
		{
			return list;
		}
	}
	while (curlist->next)
	{
		while (!strcmp(curlist->key, key))
		{
			curlist = curlist->next;
			list_delete_one(list);
			list = curlist;
			if (list == NULL)
			{
				return list;
			}
		}
		if (curlist->next == NULL)
		{
			return list;
		}
		if (!strcmp(curlist->next->key, key))
		{
			buflist = curlist->next;
			curlist->next = curlist->next->next;
			list_delete_one(buflist);
		}
		if (curlist->next == NULL)
		{
			return list;
		}
		curlist = curlist->next;
	}
	return list;
}

Pointer list_prepend(Pointer _list, char* key, Pointer data)
{
	struct List* list = _list;
	struct List* newlist;
	newlist = new(List, data, key);
	newlist->next = list;
	return newlist;
}

Pointer list_foreach(Pointer _list, void(*f)(char *key, Pointer data))
{
	struct List* list = _list;
	struct List* start_list;
	start_list = list;
	while (list != NULL)
	{
		f(list->key, list->data);
		list = list->next;
	}
	return start_list;
}

int list_has(Pointer _list, char* key)
{
	struct List* list = _list;
	while (list != NULL)
	{
		if (strcmp(list->key, key) == 0)
		{
			return 1;
		}
		list = list->next;
	}
	return 0;
}

void list_delete_one(Pointer _self)
{
	struct List* self = _self;
	delete(self->data);
	free(self);
}

Pointer list_delete(Pointer _self)
{
	struct List* self = _self;
	struct List* buf;
	while (self != NULL)
	{
		delete(self->data);
		buf = self;
		self = self->next;
		free(buf);
	}
	return self;
}

static const struct TypeDescriptor _List = {
	sizeof(struct List),
	list_create,
	list_delete
};

const void *List = &_List;
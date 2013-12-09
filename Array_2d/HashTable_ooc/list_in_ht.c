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
	char* bufstring;
	struct List* self = (struct List*)_self;
	
	self->size = va_arg(*app, size_t);
	self->data = calloc(1, self->size);
	self->data = va_arg(*app, void*);

	bufstring = va_arg(*app, char*);
	self->key = (char*)calloc(strlen(bufstring) + 1, sizeof(char));
	strcpy(self->key, bufstring);
	self->next = NULL;

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

Pointer list_prepend(Pointer _list,size_t SizeData, char* key, Pointer data)
{
	struct List* list = _list;
	struct List* newlist;
	newlist = new(List, SizeData,data, key);
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
	int i;
	struct List* buf;
	assert(self);

	while (self != NULL)
	{
		delete(self->data);
		free(self->key);
		buf = self;
		self = self->next;
		free(buf);
	}
	free(self);
	return self;
}

static const struct TypeDescriptor _List = {
	sizeof(struct List),
	list_create,
	list_delete
};

const void *List = &_List;
#include <assert.h>

#include "List.h"
#include "List_r.h"

static void * List_ctor(void * _pSelf, va_list * ppArgs)
{
	struct List * pSelf = base_ctor(List, _pSelf, ppArgs);

	char* bufstring;
	struct List* self = (struct List*)pSelf;
	self->size = va_arg(*ppArgs, size_t);
	self->data = calloc(1, self->size);
	self->data = va_arg(*ppArgs, void*);

	bufstring = va_arg(*ppArgs, char*);
	self->key = (char*)calloc(strlen(bufstring) + 1, sizeof(char));
	strcpy(self->key, bufstring);
	self->next = NULL;
		
	return pSelf;
}

static void List_draw(const void* _pSelf)
{
		int i;
		const struct List* pSelf = _pSelf;
		struct List* ForDraw = pSelf;
		printf("\n");
		printf("Распечатка всех элементов листа");
		printf("\n");

		while (ForDraw)
		{
			printf("\n");
			draw(ForDraw->data);
			printf("\n");
			ForDraw = ForDraw->next;
		}

		printf("\n");
}

static void * ListClass_ctor(void * _pSelf, va_list * ppArgs)
{
	// вызываем конструктор базового типа OBJECT_CLASS
	LIST_CLASS * pSelf = base_ctor(ListClass, _pSelf, ppArgs);

	// завершаем инициализацию, переопределение методов

	PFUNC pfnSelector = NULL; // селектор -- функция динамически связанная с методом POINT
	PFUNC pfnMethod = NULL;   // новая реализация метода POINT
	va_list pArgs = *ppArgs;

	while (1)
	{
		pfnSelector = va_arg(pArgs, PFUNC); // аргумент 5 + 2i - селектор

		if (!pfnSelector)
			break; // конец списка переопределений

		pfnMethod = va_arg(pArgs, PFUNC);   // аргумент 5 + 2i+1 - новая реализация метода

		if (pfnSelector == (PFUNC)draw)
			* (PFUNC *)&(pSelf->pfnDraw) = pfnMethod;
	}

	return pSelf;
}

static OBJECT_CLASS List_info; 
static LIST_CLASS   List_class_info; 

const void * ListClass = &List_class_info;
const void * List = &List_info;


void init_ListClass(void)
{
	inplace_new(
		&List_class_info, 
		ObjectClass,       

		"OnePropertyClass",   
		ObjectClass,        
		sizeof(LIST_CLASS), 

		ctor, ListClass_ctor,
		0
		);

	inplace_new(
		&List_info, 
		ListClass,  

		"List",       
		Object,       
		sizeof(LIST), 

		ctor, List_ctor, 
		draw, List_draw,
		dtor, List_dtor,
		0
		);
}

extern void base_draw(const void * _pClass, const void * _pSelf);

extern void draw(const void * _pSelf);

void * List_dtor(void* _self)
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

//------------------------------------------------------------------------------------
//Старые функции для листа
void* list_remove_all(void* _list, char* key)
{
	struct List* list = (struct List*)_list;
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

void* list_prepend(void* _list, char* key, struct Object* data, size_t sizedata)
{
	struct List* list = (struct List*) _list;
	struct List* newlist;
	newlist = new(List, sizedata, data, key);
	newlist->next = list;
	return newlist;
}

void* list_foreach(void* _list, void(*f)(char *key, void* data))
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

int list_has(void* _list, char* key)
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

void list_delete_one(void* _self)
{
	struct List* self = _self;
	delete(self->data);
	free(self);
}
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


/* ----------------------------------------------------------------------------------------------- *
*      объявление переменных с мета-информацией о типах POINT и POINT_CLASS
*/

static OBJECT_CLASS List_info; // мета-информация о типе POINT_CLASS
static LIST_CLASS   List_class_info;       // мета-информация о типе POINT

/* ----------------------------------------------------------------------------------------------- *
*      инициализация "красивых" констант-указателей на мета-информацию о POINT и POINT_CLASS
*/

const void * ListClass = &List_class_info;
const void * List = &List_info;


void init_ListClass(void)
{
	inplace_new(
		&List_class_info, // мета-информация о типе POINT_CLASS
		ObjectClass,       // мета-информация является экземпляром типа OBJECT_CLASS

		"OnePropertyClass",        // символическое имя типа
		ObjectClass,         // мета-информация о предке (предок POINT_CLASS -> OBJECT_CLASS)
		sizeof(LIST_CLASS), // размер типа в байтах

		ctor, ListClass_ctor,
		0
		);

	inplace_new(
		&List_info, // мета-информация о типе POINT
		ListClass,  // мета-информация является экземпляром типа POINT_CLASS

		"List",       // символическое имя типа
		Object,        // мета-информация о предке (предок POINT -> OBJECT)
		sizeof(LIST), // размер типа в байтах

		ctor, List_ctor, // переопределено динамическое связывание ctor -> Point_ctor
		draw, List_draw,
		dtor, List_dtor,
		0
		);
}

extern void base_draw(const void * _pClass, const void * _pSelf);
//{
//	const LIST_CLASS * pBaseClass = baseOf(_pClass);
//	assert(_pSelf && pBaseClass->pfnDraw);
//	pBaseClass->pfnDraw(_pSelf);
//}


extern void draw(const void * _pSelf);
//{
//	const LIST_CLASS * pClass = classOf(_pSelf);
//	assert(pClass->pfnDraw);
//	pClass->pfnDraw(_pSelf);
//}

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



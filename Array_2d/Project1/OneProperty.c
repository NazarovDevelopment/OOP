#include <assert.h>

#include "OneProperty.h"
#include "OneProperty_r.h"

static void * OneProperty_ctor(void * _pSelf, va_list * ppArgs)
{
	char* buffer;
	int i;
	struct OneProperty * pSelf = base_ctor(OneProperty, _pSelf, ppArgs);
	
	
	buffer = va_arg(*ppArgs, void*);
	pSelf->value = calloc(strlen(buffer), sizeof(char*));
	memcpy(pSelf->value, buffer, strlen(buffer)*sizeof(char*));
	return pSelf;

}

static void OneProperty_draw(const void* _pSelf)
{
	int i;
	const struct OneProperty* pSelf = _pSelf;

	printf("\n");
	for (i = 0; i < strlen(pSelf->value); i++)
	{
		printf("%c",((char*) pSelf->value)[i]);
	}
	printf("\n");
}

static void * OnePropertyClass_ctor(void * _pSelf, va_list * ppArgs)
{
	// вызываем конструктор базового типа OBJECT_CLASS
	ONEPROPERTY_CLASS * pSelf = base_ctor(OnePropertyClass, _pSelf, ppArgs);

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

static OBJECT_CLASS OneProperty_class_info; // мета-информация о типе POINT_CLASS
static ONEPROPERTY_CLASS   OneProperty_info;       // мета-информация о типе POINT

/* ----------------------------------------------------------------------------------------------- *
*      инициализация "красивых" констант-указателей на мета-информацию о POINT и POINT_CLASS
*/

const void * OnePropertyClass = &OneProperty_class_info;
const void * OneProperty = &OneProperty_info;


void init_OnePropertyClass(void)
{
	inplace_new(
		&OneProperty_class_info, // мета-информация о типе POINT_CLASS
		ObjectClass,       // мета-информация является экземпляром типа OBJECT_CLASS

		"OnePropertyClass",        // символическое имя типа
		ObjectClass,         // мета-информация о предке (предок POINT_CLASS -> OBJECT_CLASS)
		sizeof(ONEPROPERTY_CLASS), // размер типа в байтах

		ctor, OnePropertyClass_ctor,
		0
		);

	inplace_new(
		&OneProperty_info, // мета-информация о типе POINT
		OnePropertyClass,  // мета-информация является экземпляром типа POINT_CLASS

		"OneProperty",       // символическое имя типа
		Object,        // мета-информация о предке (предок POINT -> OBJECT)
		sizeof(ONEPROPERTY), // размер типа в байтах

		ctor, OneProperty_ctor, // переопределено динамическое связывание ctor -> Point_ctor
		draw, OneProperty_draw,
		dtor, OneProperty_dtor,
		0
		);
}

void base_draw(const void * _pClass, const void * _pSelf)
{
	const ONEPROPERTY_CLASS * pBaseClass = baseOf(_pClass);
	assert(_pSelf && pBaseClass->pfnDraw);
	pBaseClass->pfnDraw(_pSelf);
}


void draw(const void * _pSelf)
{
	const ONEPROPERTY_CLASS * pClass = classOf(_pSelf);
	assert(pClass->pfnDraw);
	pClass->pfnDraw(_pSelf);
}

void * OneProperty_dtor(void* _self)
{
	struct OneProperty* self = _self;
	int i;
	assert(self);
	free(self->value);
	return self;
}



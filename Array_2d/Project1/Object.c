#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Object.h"
#include "Object_r.h"


/* ----------------------------------------------------------------------------------------------- *
*      OBJECT : реализация методов
*/

static void * Object_ctor(void * _pSelf, va_list * ppArgs) { return _pSelf; }

static void * Object_dtor(void * _pSelf) { return _pSelf; }

static int Object_differ(const void * _pSelf, const void * _pOther)
{
	// разные объекты (расположенные по разным адресам) - всегда различаются
	return _pSelf != _pOther;
}

static int Object_print(const void * _pSelf, FILE * pStream)
{
	// печатаем сведения в поток
	const OBJECT_CLASS * pClass = classOf(_pSelf);
	return fprintf(pStream, "%s at %p\n", pClass->name, _pSelf);
}


/* ----------------------------------------------------------------------------------------------- *
*      OBJECT_CLASS : реализация методов
*/

static void * ObjectClass_ctor(void * _pSelf, va_list * ppArgs)
{
	//переопределённая инициализация мета-информации о типе

	OBJECT_CLASS * pSelf = _pSelf;  // мета-информация - это всегда OBJECT_CLASS или его наследники
	static const size_t offset = offsetof(OBJECT_CLASS, pfnCtor); // смещение в структуре OBJECT_CLASS до поля pfnCtor

	// аргумент 2 - символическое имя описываемого типа данных
	pSelf->name = va_arg(*ppArgs, char *);

	// аргумент 3 - мета-информация о предке описываемого типа данных
	pSelf->pBaseClass = va_arg(*ppArgs, OBJECT_CLASS *);

	// аргумент 4 - размер описываемого типа данных
	pSelf->size = va_arg(*ppArgs, size_t);

	assert(pSelf->pBaseClass);

	// набор указателей на методы скопируем из мета-информации предка
	memcpy(
		(char *)pSelf + offset,
		(char *)pSelf->pBaseClass + offset,
		sizeOf(pSelf->pBaseClass) - offset
		);

	/*
	ниже приведён код эквивалентный memcpy( ... )

	pSelf->ctor   = pSelf->pBaseClass->ctor;
	pSelf->dtor   = pSelf->pBaseClass->dtor;
	pSelf->differ = pSelf->pBaseClass->differ;
	pSelf->print  = pSelf->pBaseClass->print;
	...

	и все дальнейшие указатели будут скопированы из мета-информации предка...
	*/

	// переопределение методов
	{
		PFUNC pfnSelector = NULL; // селектор -- функция динамически связанная с методом OBJECT
		PFUNC pfnMethod = NULL;   // новая реализация метода OBJECT
		va_list pArgs = *ppArgs;

		while (1)
		{
			pfnSelector = va_arg(pArgs, PFUNC); // аргумент 5 + 2i - селектор

			if (!pfnSelector)
				break; // селектор = NULL => конец списка переопределений

			pfnMethod = va_arg(pArgs, PFUNC);   // аргумент 5 + 2i+1 - новая реализация метода

			// если селектор указывает на функцию динамического вызова конструктора
			if (pfnSelector == (PFUNC)ctor)
				// то связываем ctor в мета-информации с новой реализацией метода, и т.д.
				* (PFUNC *)&(pSelf->pfnCtor) = pfnMethod;

			else if (pfnSelector == (PFUNC)dtor)
				* (PFUNC *)&(pSelf->pfnDtor) = pfnMethod;

			else if (pfnSelector == (PFUNC)differ)
				* (PFUNC *)&(pSelf->pfnDiffer) = pfnMethod;

			else if (pfnSelector == (PFUNC)print)
				* (PFUNC *)&(pSelf->pfnPrint) = pfnMethod;
		}

		return pSelf;
	}
}

static void * ObjectClass_dtor(void * _pSelf)
{
	// уничтожать структуры с мета-информацией о типах не планируется

	OBJECT_CLASS * pSelf = _pSelf;
	fprintf(stderr, "%s: cannot destroy class\n", pSelf->name);
	return 0;
}


/* ----------------------------------------------------------------------------------------------- *
*      ручная инициализация структур с мета-информацией об OBJECT и OBJECT_CLASS
*/

static const OBJECT_CLASS object_class_info[2] =
{
	// мета-информация о типе OBJECT
	{
		// каждый экземпляр OBJECT_CLASS содержит в начале себя OBJECT
		{
			&object_class_info[1] // который указывает на мета-информацию о типе OBJECT_CLASS
		},

		"Object",              // символическое имя типа
		&object_class_info[0], // мета-информация о предке (предок OBJECT -> OBJECT)
		sizeof(OBJECT),        // размер типа в байтах

		Object_ctor,   // установлено динамическое связывание ctor   -> Object_ctor
		Object_dtor,   // установлено динамическое связывание dtor   -> Object_dtor
		Object_differ, // установлено динамическое связывание differ -> Object_differ
		Object_print   // установлено динамическое связывание print  -> Object_print
	},

	// мета-информация о типе OBJECT_CLASS
	{
		// каждый экземпляр OBJECT_CLASS содержит в начале себя OBJECT
		{
			&object_class_info[1] // который указывает на мета-информацию о типе OBJECT_CLASS
		},

		"ObjectClass",         // символическое имя типа
		&object_class_info[0], // мета-информация о предке (предок OBJECT_CLASS -> OBJECT) 
		sizeof(OBJECT_CLASS),  // размер типа байтах

		ObjectClass_ctor, // установлено динамическое связывание ctor   -> ObjectClass_ctor
		ObjectClass_dtor, // установлено динамическое связывание dtor   -> ObjectClass_dtor
		Object_differ,    // установлено динамическое связывание differ -> Object_differ (как у предка)
		Object_print      // установлено динамическое связывание print  -> Object_print (как у предка)
	}
};


/* ----------------------------------------------------------------------------------------------- *
*      инициализация "красивых" констант-указателей на мета-информацию о OBJECT и OBJECT_CLASS
*/

const void * Object = &object_class_info[0];
const void * ObjectClass = &object_class_info[1];


/* ----------------------------------------------------------------------------------------------- *
*      реализация динамического создания/уничтожения объектов
*/

void * new(const void * _pClass, ...)
{
	// создание и инициализация объекта исходя из мета-информации

	const OBJECT_CLASS * pClass = _pClass; 
	OBJECT * pSelf = NULL;                 
	va_list pArgs;

	assert(pClass && pClass->size);

	// узнаем из мета-информации размер создаваемого объекта и выделяем требуемую память
	pSelf = calloc(1, pClass->size);

	if (pSelf)
	{
		// инициализируем в только что созданном объекте указатель на мета-информацию о типе
		pSelf->pClass = pClass;

		// дальнейшая инициализация перепоручается конструктору ...
		va_start(pArgs, _pClass);
		pSelf = ctor(pSelf, &pArgs); // вызов динамически связанного конструктора
		va_end(pArgs);
	}

	return pSelf;
}


void delete(void * _pSelf)
{
	// деинициализация и удаление объекта

	if (_pSelf)
		// вызывается динамически связанный деструктор ...
		free(dtor(_pSelf)); // который возвращает указатель на освобождаемую память
}


void inplace_new(void * _pSelf, const void * _pClass, ...)
{
	// инициализация объекта в заранее выделенном блоке памяти по мета-информации о типе

	const OBJECT_CLASS * pClass = _pClass; // мета-информация - это всегда OBJECT_CLASS и его наследники
	OBJECT * pSelf = _pSelf;               // инициализируемый объект всегда наследник OBJECT
	va_list pArgs;

	if (pSelf)
	{
		// инициализируем в объекте указатель на мета-информацию о типе
		pSelf->pClass = pClass;

		// дальнейшая инициализация перепоручается конструктору ...
		va_start(pArgs, _pClass);
		pSelf = ctor(pSelf, &pArgs); // вызов динамический связаного конструктора
		va_end(pArgs);
	}
}


/* ----------------------------------------------------------------------------------------------- *
*      реализация функций с динамическим связыванием (dynamic linking)
*              динамическое связывание для 4 методов типа OBJECT и его наследников
*/

void * ctor(void * _pSelf, va_list * ppArgs)
{
	const OBJECT_CLASS * pClass = classOf(_pSelf);
	assert(pClass->pfnCtor);
	return pClass->pfnCtor(_pSelf, ppArgs);
}

void * dtor(void * _pSelf)
{
	const OBJECT_CLASS * pClass = classOf(_pSelf);
	assert(pClass->pfnDtor);
	return pClass->pfnDtor(_pSelf);
}

int differ(const void * _pSelf, const void * _pOther)
{
	const OBJECT_CLASS * pClass = classOf(_pSelf);
	assert(pClass->pfnDiffer);
	return pClass->pfnDiffer(_pSelf, _pOther);
}

int print(const void * _pSelf, FILE * pStream)
{
	const OBJECT_CLASS * pClass = classOf(_pSelf);
	assert(pClass->pfnPrint);
	return pClass->pfnPrint(_pSelf, pStream);
}


/* ----------------------------------------------------------------------------------------------- *
*      вспомогательные функции для вызова методов базового типа
*              допустим вызов этих 4 функций для наследников OBJECT, т.е. у всех типов в иерархии
*/

void * base_ctor(const void * _pClass, void * _pSelf, va_list * ppArgs)
{
	const OBJECT_CLASS * pBaseClass = baseOf(_pClass);
	assert(_pSelf && pBaseClass->pfnCtor);
	return pBaseClass->pfnCtor(_pSelf, ppArgs);
}

void * base_dtor(const void * _pClass, void * _pSelf)
{
	const OBJECT_CLASS * pBaseClass = baseOf(_pClass);
	assert(_pSelf && pBaseClass->pfnDtor);
	return pBaseClass->pfnDtor(_pSelf);
}

int base_differ(const void * _pClass, const void * _pSelf, const void * _pOther)
{
	const OBJECT_CLASS * pBaseClass = baseOf(_pClass);
	assert(_pSelf && pBaseClass->pfnDiffer);
	return pBaseClass->pfnDiffer(_pSelf, _pOther);
}

int base_print(const void * _pClass, const void * _pSelf, FILE * pStream)
{
	const OBJECT_CLASS * pBaseClass = baseOf(_pClass);
	assert(_pSelf && pBaseClass->pfnPrint);
	return pBaseClass->pfnPrint(_pSelf, pStream);
}


/* ----------------------------------------------------------------------------------------------- *
*      реализация вспомогательных функции для извлечения мета-информации о типе
*/

const void * classOf(const void * _pSelf)
{
	// получение мета-информации о типе переданного объекта
	const OBJECT * pSelf = _pSelf;
	assert(pSelf && pSelf->pClass);
	return pSelf->pClass;
}

size_t sizeOf(const void * _pSelf)
{
	// получение размера переданного объекта
	const OBJECT_CLASS * pClass = classOf(_pSelf);
	return pClass->size;
}

const void * baseOf(const void * _pClass)
{
	// получение мета-информации о базовом типе
	const OBJECT_CLASS * pClass = _pClass;
	assert(pClass && pClass->pBaseClass);
	return pClass->pBaseClass;
}
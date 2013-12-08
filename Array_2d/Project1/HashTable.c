#include <assert.h>
#include <string.h>

#include "HashTable.h"
#include "HashTable_r.h"

typedef unsigned(*HashFunction)(char *key);

void* HashTable_dtor(void* _self);

unsigned jenkins_one_at_a_time_hash(char *key) {
	unsigned hash = 0;

	for (; *key; ++key) {
		hash += *key;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

static void * HashTable_ctor(void * _pSelf, va_list * ppArgs)
{
	struct HashTable * pSelf = base_ctor(HashTable, _pSelf, ppArgs);
	HashFunction hf = NULL;
	
	pSelf->size = va_arg(*ppArgs, size_t);
	pSelf->table = (struct List**)calloc(pSelf->size, sizeof(struct List*));

	hf = va_arg(*ppArgs, HashFunction);
	if (hf != NULL)
	{
		pSelf->hf = hf;
	}
	else
	{
		pSelf->hf = jenkins_one_at_a_time_hash;
	}
	
	
	return pSelf;
}

static void HashTable_draw(const void * _pSelf)
{
	// рисование точки (отсутствует у предка)

	const struct HashTable * pSelf = _pSelf;
	int i;

	for (i = 0; i < pSelf->size; i++)
	{
		draw(pSelf->table[i]);
	}
}

/* ----------------------------------------------------------------------------------------------- *
*      POINT_CLASS : реализация методов
*/

// PointClass_ctor() -- инициализация структуры с мета-информацией о типе

static void * HashTableClass_ctor(void * _pSelf, va_list * ppArgs)
{
	// переопределённая инициализация мета-информации о типе POINT

	// вызываем конструктор базового типа OBJECT_CLASS
	HASHTABLE_CLASS * pSelf = base_ctor(HashTableClass, _pSelf, ppArgs);

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

static OBJECT_CLASS HashTable_class_info; // мета-информация о типе POINT_CLASS
static HASHTABLE_CLASS  HashTable_info;       // мета-информация о типе POINT

/* ----------------------------------------------------------------------------------------------- *
*      инициализация "красивых" констант-указателей на мета-информацию о POINT и POINT_CLASS
*/

const void * HashTableClass = &HashTable_class_info;
const void * HashTable = &HashTable_info;

/* ----------------------------------------------------------------------------------------------- *
*      автоматическая инициализация структур с мета-информацией об POINT и POINT_CLASS
*/

void init_HashTableClass(void)
{
	inplace_new(
		&HashTable_class_info, // мета-информация о типе POINT_CLASS
		ObjectClass,       // мета-информация является экземпляром типа OBJECT_CLASS

		"HashTasbleClass",        // символическое имя типа
		ObjectClass,         // мета-информация о предке (предок POINT_CLASS -> OBJECT_CLASS)
		sizeof(HASHTABLE_CLASS), // размер типа в байтах

		ctor, HashTableClass_ctor, // переопределено динамическое связывание ctor->PointClass_ctor
		0
		);

	inplace_new(
		&HashTable_info, // мета-информация о типе POINT
		HashTableClass,  // мета-информация является экземпляром типа POINT_CLASS

		"HashTable",       // символическое имя типа
		Object,        // мета-информация о предке (предок POINT -> OBJECT)
		sizeof(HASHTABLE), // размер типа в байтах

		ctor, HashTable_ctor, // переопределено динамическое связывание ctor -> Point_ctor
		draw, HashTable_draw,// установлено динамическое связывание    draw -> Point_draw
		dtor, HashTable_dtor,
		0
		);
}


/* ----------------------------------------------------------------------------------------------- *
*      реализация функций с динамическим связыванием (dynamic linking)
*              динамическое связывание 1 метода для типа POINT и его наследников
*/


void* HashTable_dtor(void* _self)
{
	int i;
	HASHTABLE* self = _self;

	for (i = 0; i<self->size; i++)
	{
		delete(self->table[i]);
	}

	free(self->table);
	return self;
}

extern void draw(const void * _pSelf);


/* ----------------------------------------------------------------------------------------------- *
*      вспомогательная функция вызывающие методы базового типа
*              допустим вызов этой функции для наследников POINT
*/

extern void base_draw(const void * _pClass, const void * _pSelf);

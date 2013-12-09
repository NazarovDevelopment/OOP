#include <assert.h>
#include <string.h>

#include "HashTable.h"
#include "HashTable_r.h"

#include "OneProperty.h"
#include "OneProperty_r.h"

#include "List.h"
#include "List_r.h"

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
		if (pSelf->table[i])
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

static OBJECT_CLASS HashTable_class_info; 
static HASHTABLE_CLASS  HashTable_info;   


const void * HashTableClass = &HashTable_class_info;
const void * HashTable = &HashTable_info;

void init_HashTableClass(void)
{
	inplace_new(
		&HashTable_class_info,
		ObjectClass,       

		"HashTasbleClass",  
		ObjectClass,        
		sizeof(HASHTABLE_CLASS), 

		ctor, HashTableClass_ctor,
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

extern void base_draw(const void * _pClass, const void * _pSelf);

//---------------------------------------------------------------------------------------------------------------
//Старые функции для хэш

void* ht_set(void* _self, char *key, void* data, size_t sizedata)
{
	HASHTABLE* self = _self;
	LIST* newlist;
	LIST* buf;
	unsigned index;
	int ddd;

	index = self->hf(key) % self->size;
	buf = self->table[index];
	while (buf != NULL)
	{
		if (strcmp(buf->key, key) == 0)
		{
			delete(buf->data);
			buf->data = (struct Object*)data;
			return self;
		}
		buf = buf->next;
	}
	self->table[index] = list_prepend(self->table[index], key, data, sizedata);
	return self;
}

void* ht_get(void* _self, char *key)
{
	struct HashTable* self = _self;
	size_t index;
	struct List * buf;
	index = self->hf(key) % self->size;
	buf = self->table[index];
	while (buf != NULL)
	{
		if (strcmp(buf->key, key) == 0)
		{
			return buf->data;
		}
		buf = buf->next;
	}
	return NULL;
}

int ht_has(void* _self, char *key)
{
	struct HashTable* self = _self;
	size_t index;
	struct List * buf;
	index = self->hf(key) % self->size;
	buf = self->table[index];
	if (list_has(buf, key) == 1)
	{
		return 1;
	}
	return 0;
}

void* ht_delete(void* _self, char* key)
{
	struct HashTable* self = _self;
	size_t index;
	index = self->hf(key) % self->size;
	if (!self->table[index])
	{
		return self;
	}
	self->table[index] = list_remove_all(self->table[index], key);
	return self;
}

void* ht_traverse(void* _self, void(*f)(char *key, void* data))
{
	struct HashTable* self = _self;
	size_t i;
	struct List * buf;
	for (i = 0; i<self->size; i++)
	{
		buf = self->table[i];
		list_foreach(buf, f);
	}
	return self;
}

void* ht_resize(void* _self, size_t new_size)
{
	struct HashTable* self = _self;
	struct List ** new_table;
	struct List * buf;
	size_t i;
	size_t index;
	new_table = (struct List**)calloc(new_size, sizeof(struct List*));
	for (i = 0; i<self->size; i++)
	{
		buf = self->table[i];
		while (buf != 0)
		{
			index = self->hf(buf->key) % new_size;
			new_table[index] = (struct List*) list_prepend(new_table[index], buf->key, buf->data, buf->size);
			buf = buf->next;
		}
		delete(self->table[i]);
	}
	free(self->table);
	self->table = new_table;
	self->size = new_size;
	return self;
}
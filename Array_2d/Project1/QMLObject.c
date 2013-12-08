#include <stdio.h>

#include "QMLObject.h"
#include "QMLObject_r.h"

#include "HashTable_r.h"
#include "HashTable.h"


static void * QmlObject_ctor(void * _pSelf, va_list * ppArgs)
{
	struct QmlObject * pSelf = base_ctor(QmlObject, _pSelf, ppArgs);
	char* buffer = va_arg(*ppArgs, char*);
	pSelf->ValidPropertiesString = calloc(strlen(buffer) + 1, sizeof(char));
	strcpy(pSelf->ValidPropertiesString, buffer);
	return pSelf;
}

void * QmlObject_dtor(void* _self)
{
	QMLOBJECT* self = _self;
	HashTable_dtor(&self->_);
	free(self->ValidPropertiesString);
	return self;
}

static void QmlObject_draw(const void * _pSelf)
{
	// переопределённое рисование

	const QMLOBJECT * pSelf = _pSelf;
	const HASHTABLE * pBase = _pSelf;

}

/* ----------------------------------------------------------------------------------------------- *
*      объявление переменных с мета-информацией о типе CIRCLE
*/

static HASHTABLE_CLASS QmlObject_info; // мета-информация о типе CIRCLE

/* ----------------------------------------------------------------------------------------------- *
*      инициализация "красивых" констант-указателей на мета-информацию о CIRCLE
*/

const void * QmlObject = &QmlObject_info;


void init_QmlObjectClass(void)
{
	init_HashTableClass();

	inplace_new(
		&QmlObject_info, // мета-информация о типе CIRCLE
		HashTableClass,   // мета-информация является экземпляром типа POINT_CLASS

		"QmlObject",       // символическое имя типа
		HashTable,          // мета-информация о предке (предок CIRCLE -> POINT)
		sizeof(QMLOBJECT), // размер типа в байтах

		ctor, QmlObject_ctor, // переопределено динамическое связывание ctor -> Circle_ctor
		draw, QmlObject_draw,
		dtor, QmlObject_dtor,
		0
		);
}

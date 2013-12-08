#ifndef QMLOBJECT_H
#define QMLOBJECT_H

#include "HashTable.h"

/* ----------------------------------------------------------------------------------------------- *
*      "красивые" константы-указатели на мета-информацию об CIRCLE
*/

extern const void * QmlObject;     // использование: new(Circle, x, y, rad);

/* ----------------------------------------------------------------------------------------------- *
*      вспомогательные функции для инициализации мета-информации о типе
*/

void init_QmlObjectClass(void);


void MyParser(struct QmlObject* Qobject, FILE *pFile);



#endif
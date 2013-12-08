#ifndef QMLOBJECT_R
#define QMLOBJECT_R

#include "HashTable_r.h"

typedef struct QmlObject QMLOBJECT;

/* ----------------------------------------------------------------------------------------------- *
*      CIRCLE : окружность в 2-мерном пространстве (целочисленные координаты)
*/

struct QmlObject
{
	const HASHTABLE _;

	char* ValidPropertiesString;
};

#endif
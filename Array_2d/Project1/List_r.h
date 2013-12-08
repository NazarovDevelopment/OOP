#ifndef LIST_R
#define LIST_R

#include "Object_r.h"

typedef struct List LIST;
typedef struct ListClass LIST_CLASS;


struct List
{
	const OBJECT _;

	char *key;
	size_t size;
	void* data;
	struct List *next;
};

struct ListClass
{
	const OBJECT_CLASS _;

	void(*pfnDraw)(const void *_pSelf);
};

extern void base_draw(const void * _pClass, const void * _pSelf);

#endif
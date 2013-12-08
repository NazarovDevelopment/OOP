#ifndef ONEPROPERTY_R
#define ONEPROPERTY_R

#include "Object_r.h"

typedef struct OneProperty ONEPROPERTY;
typedef struct OnePropertyClass ONEPROPERTY_CLASS;


struct OneProperty
{
	const OBJECT _;

	void* value;
};

struct OnePropertyClass
{
	const OBJECT_CLASS _; 

	void(*pfnDraw)(const void *_pSelf);
};

void base_draw(const void * _pClass, const void * _pSelf);

#endif
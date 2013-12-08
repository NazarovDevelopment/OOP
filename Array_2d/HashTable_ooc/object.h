#if !defined(_OBJECT_H_)
#define _OBJECT_H_

#include "new.h"

typedef void* Pointer;

struct Object
{
	const void *class;
	unsigned r, g, b;
};

extern const void *Object;

#endif

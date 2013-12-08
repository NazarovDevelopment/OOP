#if !defined(_OBJECT_H_)
#define _OBJECT_H_

#include "new.h"

typedef void* Pointer;

struct Object
{
	const void *TypeDescriptor;
	void* value;
};

extern const void *Object;

#endif

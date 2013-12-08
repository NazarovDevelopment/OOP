#include <stdlib.h>
#include <assert.h>
#include "new.h"

void * new(const void *_type, ...)
{
	const struct TypeDescriptor *type = _type;
	void *p = calloc(1, type->size);
	assert(p);

	*(const struct TypeDescriptor **)p = type;
	if (type->ctor)
	{
		va_list ap;
		va_start(ap, _type);
		p = type->ctor(p, &ap);
		va_end(ap);
	}

	return p;
}

void* delete(void *self)
{
	const struct TypeDescriptor **cp = self;

	if (self && *cp && (*cp)->dtor)
	{
		self = (*cp)->dtor(self);
	}

	free(self);
}
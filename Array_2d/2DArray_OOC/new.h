#ifndef NEW_H
#define NEW_H

#include <assert.h>
#include <stdlib.h>

struct TypeDescriptor{
	size_t size;
	void * (* ctor) (void * self, va_list * app);
    void * (* dtor) (void * self);
};

void * new (const void * type, ...);
void delete (void * item);

#endif
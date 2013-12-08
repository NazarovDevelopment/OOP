#if !defined (NEW_H)
#define NEW_H

#include <stddef.h>
#include <stdarg.h>

struct TypeDescriptor
{
	size_t size;
	void *(*ctor)(void *self, va_list *app);
	void *(*dtor)(void *self);
	void *(*Draw)(void *self);
};

void *new(const void *type, ...);
void *delete(void *item);
#endif  

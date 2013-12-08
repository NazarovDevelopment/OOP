#include "new.h"


void * new (const void * _type, ...)
{
	const struct TypeDescriptor * type = (const struct TypeDescriptor*)_type;
    void * p = malloc(type->size);
    assert(p);
	
	*(const struct TypeDescriptor **) p = type;

    if (type->ctor)
	{
		va_list ap;
        _crt_va_start(ap, _type);
        p = type->ctor(p, &ap);
		_crt_va_end(ap);
    }

        return p;
}
void delete (void * self)
{
        const struct TypeDescriptor ** cp = ( const struct TypeDescriptor **) self;
        
        if (self && * cp && (* cp)->dtor)
                self = (* cp)->dtor(self);
        
}


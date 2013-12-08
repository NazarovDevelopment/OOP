#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "object.h"
#include "new.h"

static Pointer object_create(Pointer _self, va_list *app)
{
	struct Object* self = _self;
	self->r = va_arg(*app, unsigned);
	self->g = va_arg(*app, unsigned);
	self->b = va_arg(*app, unsigned);
	return self;
}

static Pointer object_destroy(Pointer _self)
{
	struct Object* self = _self;
	assert(self);
	return self;
}

static const struct TypeDescriptor _Object = {
	sizeof(struct Object),
	object_create,
	object_destroy
};

const void *Object = &_Object;
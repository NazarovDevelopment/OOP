#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "object.h"
#include "new.h"

static Pointer object_create(Pointer _self, va_list *app)
{
	struct Object* self = _self;
	char* buffer;
	int i;
	buffer = va_arg(*app, void*);
	self->value = calloc(strlen(buffer),sizeof(char*));
	memcpy(self->value, buffer, strlen(buffer)*sizeof(char*));
	return self;
}

static Pointer object_destroy(Pointer _self)
{
	struct Object* self = _self;
	int i;
	assert(self);
	free(self->value);
	return self;
}

static const struct TypeDescriptor _Object = {
	sizeof(struct Object),
	object_create,
	object_destroy
};

const void *Object = &_Object;
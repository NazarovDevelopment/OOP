#ifndef ONEPROPERTY_H
#define ONEPROPERTY_H

#include "Object.h"

extern const void * OneProperty;    
extern const void * OnePropertyClass;

void draw(const void* _pSelf);

void* OneProperty_dtor(void *_pSelf);

void init_OnePropertyClass(void);

#endif
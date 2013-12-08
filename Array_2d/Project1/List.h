#ifndef LIST_H
#define LIST_H

#include "Object.h"

extern const void * List;
extern const void * ListClass;

extern void draw(const void* _pSelf);

void* List_dtor(void *_pSelf);

void init_ListClass(void);

#endif
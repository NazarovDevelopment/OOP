#ifndef ARRAY_2D_H
#define ARRAY_2D_H

#include <assert.h>
#include <stdio.h>
#include "New.h"

typedef void* Pointer;
enum pozition {up = 0, right, down, left};

struct Array2d
{
	const struct TypeDescriptor * type;
	Pointer **data;
	int width;
	int height;
	size_t size_box;

};

//void print(const void *_self)
//{
//	int i,j;
//	struct Array2d* self = (struct Array2d*)_self;
//
//	for(i = 0; i < self->height; i++)
//	{
//		for(j = 0; j < self->width; j++)
//			printf("%i", self->data[i][j]);
//	}
//}
/*
*функция показывает значение с индексом [x][y]
*/
Pointer Find(struct Array2d* arr, int x, int y);

/*
*изменить размер массива
*пустота заполняется нулями
*лишнее теряется
*/
struct Array2d* re_size_Array2d(struct Array2d* arr, int new_width, int new_height);

/*
*вставить arr_old in arr_new
*/
void paste_arr2d(struct Array2d* arr_old, struct Array2d* arr_new, int y, int x);

/*
*функция добавляет к переданному ей массиву строки или столбцы на выбор,
*второй аргумент выбор того что нужно дбавить: line or column
*третий аргумент задает позицию: left or right, up or down
*четвертыый аргумент азадет количество строк или столбцов
*/
struct Array2d * add_the_part(struct Array2d *arr, enum pozition poz, int counter);

/*
*положить значение по адресу
*/
void put_value(struct Array2d *arr, Pointer value, int x, int y);


static void * Array2d_ctor (void * _self, va_list * app)
{
	struct Array2d* self = (struct Array2d*)_self;
	int i,j;

	self->height = _crt_va_arg(*app, int);
	self->width  = _crt_va_arg(*app, int);
	self->size_box = _crt_va_arg(*app, size_t);

	self->data = (Pointer**) malloc(self->width*sizeof(Pointer*));
		
	for ( i = 0; i < self->width; i ++)
	{
		self->data[i] = (Pointer*) malloc (self->height*self->size_box);
	}

	for (  i = 0; i < self->width; i ++)
		for ( j = 0; j < self->height; j++)
	{
		self->data[i][j] = NULL;
	}

 return self;
}

static void * Array2d_dtor(void * _self)
{
	struct Array2d * self = (struct Array2d *)_self;
	int i;
	
	for (i=0; i<self->width;i++)
	free (self->data[i]);
	free(self->data);
	free(self);
    
	return self;
}
static const struct TypeDescriptor _Array2d =
{
	sizeof(struct Array2d),
        Array2d_ctor,
        Array2d_dtor
		 //   ,print
};
#endif

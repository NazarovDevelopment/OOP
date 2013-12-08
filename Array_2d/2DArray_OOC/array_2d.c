#include "array_2d.h"
#include "new.h"
//static const size_t _Set = sizeof(struct Set);
//static const size_t _Object= sizeof(struct Object);


const void* Array2d = &_Array2d;

int minimum(int a, int b)
{
	 if(a<b) return a;
	 return b;
}
void copy_array2d(struct Array2d* arr1, struct Array2d* arr2){
	int i, im = minimum(arr1->width, arr2->width);
	int j,jm = minimum(arr1->height, arr2->height);;

	for (i = 0; i < im; i++)
		for (j = 0; j <jm; j++)
			arr2->data[i][j] = arr1->data[i][j];
}

void error2d(struct Array2d* arr)
{
	if(arr==NULL)
	{
		printf("aaaaaaaaa");
		return;
	}
}

Pointer Find(struct Array2d* arr, int x, int y){
	error2d(arr);
	return arr->data[x][y];
}

struct Array2d *re_size_Array2d(struct Array2d* arr, int new_width, int new_height)
{ 
	 struct Array2d* new_array;
	//= (Array2d*) malloc (sizeof(Array2d));

	new_array = ( struct Array2d*) new(Array2d, new_width, new_height, arr->size_box);
	copy_array2d(arr, new_array);
	delete(arr);
	//arr = (Array2d*) malloc (1*sizeof(Array2d));
	//arr = create_Array2d(new_width, new_height);
	//copy_array2d(new_array,arr);
	//destroy_array2d(arr);

	return new_array;
}

void paste_arr2d(struct Array2d* arr_old, struct Array2d* arr_new, int x, int y)
{
	int i,j;

	int max_x = arr_old->height;
	int max_y = arr_old->width;

	if (max_x > arr_new->height-x)
		max_x = arr_new->height-x;

	if (max_y > arr_new->width-y)
		max_y = arr_new->width-y;

	for (i = 0; i < max_y; i++)
	{
		for (j = 0; j < max_x; j++)
		{
			arr_new->data[y+i][x+j] = arr_old->data[i][j];
		}
	}

}

struct Array2d* add_the_part(struct Array2d *arr, enum pozition poz, int counter)
{
	struct Array2d *new_array;

	switch (poz)
	{
	case up:

		new_array = new(Array2d, arr->width + counter, arr->height, arr->size_box);
		paste_arr2d(arr, new_array, 0, counter);
		delete(arr);
		
		return new_array;

	case right:

//		re_size_Array2d(arr, arr->width, arr->height + counter);

		new_array = new(Array2d,arr->width, arr->height + counter, arr->size_box);
		paste_arr2d(arr, new_array, 0, 0);
		delete(arr);
		arr = new_array;
		return arr;

	case down:

	//	re_size_Array2d(arr, arr->width + counter, arr->height);
	
		new_array = new(Array2d,arr->width + counter, arr->height, arr->size_box);
		paste_arr2d(arr, new_array, 0,0);
		delete(arr);
		arr = new_array;
		return arr;
		
	case left:

		new_array = new(Array2d,arr->width, arr->height + counter, arr->size_box);
		paste_arr2d(arr, new_array, counter, 0);
		delete(arr);
		arr = new_array;
		return arr;

	default:
		break;
	}



}

void put_value(struct Array2d *arr, Pointer value, int x, int y)
{
	arr->data[x][y] = value;
}

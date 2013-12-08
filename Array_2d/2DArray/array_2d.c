
#include "array_2d.h"

int minimum(int a, int b)
{
	 if(a<b) return a;
	 return b;
}
void copy_array2d(Array2d* arr1, Array2d* arr2){
	int i, im = minimum(arr1->width, arr2->width);
	int j,jm = minimum(arr1->height, arr2->height);;

	for (i = 0; i < im; i++)
		for (j = 0; j <jm; j++)
			arr2->data[i][j] = arr1->data[i][j];
}

void error2d(Array2d* arr)
{
	if(arr==NULL)
	{
		printf("aaaaaaaaa");
		return;
	}
}

/*
*создать 2d массив
*/
Array2d* create_Array2d( int width, int height, size_t size_box)
{
	Array2d *arr = (Array2d*) malloc(sizeof(Array2d));
	int i,j;
	error2d(arr);
	arr->height = height;
	arr->width= width;
	arr->size_box = size_box;

	arr->data = (Pointer**) malloc(width*sizeof(Pointer*));
	for ( i = 0; i < width; i ++)
	{
		arr->data[i] = (Pointer*) malloc (height*arr->size_box);
	}

	for (  i = 0; i < width; i ++)
		for ( j = 0; j < height; j++)
		{
			arr->data[i][j] = NULL;
		}

		return arr;

}
/*
*удалить 2d массив
*/

void destroy_array2d(Array2d *arr)
{
	int i;
	error2d(arr);
	
	for (i=0; i<arr->width;i++)
		free (arr->data[i]);
		free(arr->data);
		free(arr);
}

/*
*найти
*/

Pointer Find(Array2d* arr, int x, int y){
	error2d(arr);
	return arr->data[x][y];
}

Array2d *re_size_Array2d(Array2d* arr, int new_width, int new_height)
{ 
	 Array2d* new_array;
	//= (Array2d*) malloc (sizeof(Array2d));

	new_array = create_Array2d(new_width, new_height, arr->size_box);
	copy_array2d(arr, new_array);
	destroy_array2d(arr);
	//arr = (Array2d*) malloc (1*sizeof(Array2d));
	//arr = create_Array2d(new_width, new_height);
	//copy_array2d(new_array,arr);
	//destroy_array2d(arr);

	return new_array;
}

void paste_arr2d(Array2d* arr_old, Array2d* arr_new, int x, int y)
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

Array2d* add_the_part(Array2d *arr, enum pozition poz, int counter)
{
	Array2d *new_array;

	switch (poz)
	{
	case up:

		new_array = create_Array2d(arr->width + counter, arr->height, arr->size_box);
		paste_arr2d(arr, new_array, 0, counter);
		destroy_array2d(arr);
		
		return new_array;

	case right:

//		re_size_Array2d(arr, arr->width, arr->height + counter);

		new_array = create_Array2d(arr->width, arr->height + counter, arr->size_box);
		paste_arr2d(arr, new_array, 0, 0);
		destroy_array2d(arr);
		arr = new_array;
		return arr;

	case down:

	//	re_size_Array2d(arr, arr->width + counter, arr->height);
	
		new_array = create_Array2d(arr->width + counter, arr->height, arr->size_box);
		paste_arr2d(arr, new_array, 0,0);
		destroy_array2d(arr);
		arr = new_array;
		return arr;
		
	case left:

		new_array = create_Array2d(arr->width, arr->height + counter, arr->size_box);
		paste_arr2d(arr, new_array, counter, 0);
		destroy_array2d(arr);
		arr = new_array;
		return arr;

	default:
		break;
	}



}

void put_value(Array2d *arr, Pointer value, int x, int y)
{
	arr->data[x][y] = value;
}

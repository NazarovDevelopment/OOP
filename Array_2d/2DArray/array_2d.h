#include <stdlib.h>
#include <stdio.h>

typedef void* Pointer;

enum pozition {up = 0, right, down, left};


typedef struct Array_2d
{
	Pointer **data;
	
	int width;
	int height;

	size_t size_box;
} Array2d;

/*
*создать массив 2d
*/
Array2d* create_Array2d(int width, int height, size_t size_box);
 
/*
*уничтожить массив 2d
*/
void destroy_array2d(Array2d *arr);

/*
*функция показывает значение с индексом [x][y]
*/
Pointer Find(Array2d* arr, int x, int y);

/*
*изменить размер массива
*пустота заполняется нулями
*лишнее теряется
*/
Array2d * re_size_Array2d(Array2d* arr, int new_width, int new_height);

/*
*вставить arr_old in arr_new
*/
void paste_arr2d(Array2d* arr_old, Array2d* arr_new, int y, int x);

/*
*функция добавляет к переданному ей массиву строки или столбцы на выбор,
*второй аргумент выбор того что нужно дбавить: line or column
*третий аргумент задает позицию: left or right, up or down
*четвертыый аргумент азадет количество строк или столбцов
*/
Array2d * add_the_part(Array2d *arr, enum pozition poz, int counter);

/*
*положить значение по адресу
*/
void put_value(Array2d *arr, Pointer value, int x, int y);


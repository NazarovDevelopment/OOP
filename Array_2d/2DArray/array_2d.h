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
*������� ������ 2d
*/
Array2d* create_Array2d(int width, int height, size_t size_box);
 
/*
*���������� ������ 2d
*/
void destroy_array2d(Array2d *arr);

/*
*������� ���������� �������� � �������� [x][y]
*/
Pointer Find(Array2d* arr, int x, int y);

/*
*�������� ������ �������
*������� ����������� ������
*������ ��������
*/
Array2d * re_size_Array2d(Array2d* arr, int new_width, int new_height);

/*
*�������� arr_old in arr_new
*/
void paste_arr2d(Array2d* arr_old, Array2d* arr_new, int y, int x);

/*
*������� ��������� � ����������� �� ������� ������ ��� ������� �� �����,
*������ �������� ����� ���� ��� ����� �������: line or column
*������ �������� ������ �������: left or right, up or down
*���������� �������� ������ ���������� ����� ��� ��������
*/
Array2d * add_the_part(Array2d *arr, enum pozition poz, int counter);

/*
*�������� �������� �� ������
*/
void put_value(Array2d *arr, Pointer value, int x, int y);


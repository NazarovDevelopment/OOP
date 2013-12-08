#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "new.h"
#include "array_2d.h"


extern const void * Array2d;

void main()
{
	int i,j;

	struct Array2d* arr1 = new(Array2d, 2, 2, sizeof(int)); 
	struct Array2d* arr2 = new(Array2d, 5, 5, sizeof(int)); 


	arr1->data[0][0] = (Pointer) 1;
	arr1->data[0][1] = (Pointer) 2;
	arr1->data[1][0] = (Pointer) 3;
	arr1->data[1][1] = (Pointer) 4;
/*
	printf("\n%i\n", arr1->data[0][1]);
	printf("%i\n", arr1->data[1][1]);
	printf("%i\n", arr1->data[1][0]);
	printf("%i\n", arr1->data[0][0]);*/
	//
	paste_arr2d(arr1, arr2, 4,4);

	//re_size_Array2d(arr2,7,7);

	arr2 = add_the_part(arr2, down, 2);

	arr2 = re_size_Array2d(arr2, 7, 7);

	for(i = 0; i < arr2->width; i++)
	{
		for(j = 0; j < arr2->height; j++)
		{
			printf("%i ",(int)arr2->data[i][j]);		
		}
		printf("\n");
	}

	delete(arr1);
	delete(arr2);

	system("pause");

	_CrtDumpMemoryLeaks();
}
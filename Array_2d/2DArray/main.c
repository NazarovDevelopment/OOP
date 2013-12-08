#include "array_2d.h"

#include <stdio.h>
#include <stdlib.h>

#include <crtdbg.h>

typedef struct RGB{

	char R, G, B, U, F, O, D;
}Rgb;


//Rgb* create_RGB(Rgb* rgb)
//{
//	rgb = (Rgb*) malloc(sizeof(Rgb));
//	rgb->R=rgb->G=rgb->B=rgb->U=rgb->F=rgb->O=rgb->D = 'o';
//}


void main()
{
	Array2d * arr ;
	Rgb* rgb;

//------------------------------------------
	rgb = (Rgb*) malloc(sizeof(Rgb));

	arr = create_Array2d (2,2,sizeof(struct RGB));
	
	arr->data[0][0] = &rgb;
	arr->data[1][0] = &rgb;
	arr->data[0][1] = &rgb;
	arr->data[1][1] = &rgb;

	destroy_array2d(arr); 
	free(rgb);
	_CrtDumpMemoryLeaks();

	
	system("pause");
}

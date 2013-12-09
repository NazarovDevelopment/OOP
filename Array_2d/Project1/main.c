#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "OneProperty.h"
#include "OneProperty_r.h"

#include "List.h"
#include "List_r.h"

#include "HashTable.h"
#include "HashTable_r.h"

#include "QMLObject.h"
#include "QMLObject_r.h"



void main()
{
	FILE* pFile;
	errno_t ErrorInTheFile;
	char* buffer;
	ONEPROPERTY * fff;
	int i;

	init_OnePropertyClass();
	init_ListClass();
	init_QmlObjectClass();

	QMLOBJECT *a = new(QmlObject, 1, NULL, /*NULL,*/ "_x_y_width_height_id_color_");

	ErrorInTheFile = fopen_s(&pFile, "Button.txt", "r");
	if (ErrorInTheFile == 0)
	{
		MyParser(a, pFile);
	}
	else
	{
		printf("ERROR");
	}

	fff = (struct Object*)a->_.table[0]->next->data;
	buffer = fff->value;
	
	for (i = 0; i < strlen(buffer); i++)
	{
		printf("%c", buffer[i]);
	}
	printf("\n");

	delete(a);
	_CrtDumpMemoryLeaks();
	system("pause");
}
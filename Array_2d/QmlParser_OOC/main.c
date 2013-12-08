#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include <string.h>
#include "object.h"
#include "new.h"
#include "list_in_ht.h"
#include "HashTable_ooc.h" 
#include "QMLHASH.h"

void main()
{
	FILE* pFile;
	errno_t ErrorInTheFile;
	char* buffer;
	struct Object * fff;
	int i;
	struct QmlObject *a = new(QmlObject, 1, NULL, /*NULL,*/ "_x_y_width_height_id_color_");

	ErrorInTheFile = fopen_s(&pFile,"Button.txt", "r");
	if (ErrorInTheFile == 0)
	{
	MyParser(a, pFile);
	}
	else
	{
	printf("ERROR");
	}
	//assert(ht_get((Pointer)a->InternalHashTable, "id") == "QMLObject");
	
	fff = (struct Object*)a->InternalHashTable.table[0]->next->data;
	buffer = fff->value;
	for (i = 0; i < strlen(buffer); i++)
	{
		printf("%c", buffer[i]);
	}
	printf("\n");

	//printf("\n%d\n", jenkins_one_at_a_time_hash("vasya"));
	delete(a);

	system("pause");
 	_CrtDumpMemoryLeaks();
}

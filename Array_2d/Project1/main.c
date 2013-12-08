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
	ONEPROPERTY* tmp;
	LIST* example;
	HASHTABLE* gg;
	
	void* pOneProperty = NULL;
	void* pList = NULL;
	void* pHash = NULL;
	void* pQml = NULL;

	init_OnePropertyClass();
	pOneProperty = new(OneProperty, "HELLO");
	draw(pOneProperty);

	init_ListClass();
	pList = new(List,0,0, "hello");

	init_QmlObjectClass();
	pHash = new(HashTable, 5, NULL);
	pQml = new(QmlObject, 5, NULL, "EXAMPLE");

	delete(pOneProperty);
	delete(pList);
	delete(pHash);
	delete(pQml);

	_CrtDumpMemoryLeaks();
	system("pause");
}
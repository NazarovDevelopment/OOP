#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <crtdbg.h>

#include "OneProperty.h"
#include "List.h"

using namespace std;

OneProperty* test()
{
	OneProperty* pTest;
	pTest = new OneProperty("TEST");
	return pTest;
}

void main()
{
	OneProperty* pOProp = NULL;
	List* pList = NULL;
	char* StringForPut = "HELLO";

	pOProp = new OneProperty(StringForPut);
	pList = new List("test", StringForPut);

	pList->draw();
	pList = pList->prepend("name", "alexey");
	//pOProp->draw();

	delete(pList);
	delete(pOProp);

	_CrtDumpMemoryLeaks();
	system("pause");
}
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
	char* StringForPut = "HELLO";

	pOProp = new OneProperty(StringForPut);

	pOProp->draw();

	delete(pOProp);

	_CrtDumpMemoryLeaks();
	system("pause");
}
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <crtdbg.h>

#include "OneProperty.h"
#include "List.h"
#include "HashTable.h"

using namespace std;

OneProperty* test()
{
	OneProperty* pTest;
	pTest = new OneProperty("TEST");
	return pTest;
}

void main()
{
	HashTable* pHash = new HashTable(1);
	pHash->set("name", "vasiliy");
	pHash->set("id", "property");
		
	char* test = (char*) pHash->get("id");

	delete(pHash);
	_CrtDumpMemoryLeaks();
	system("pause");
}
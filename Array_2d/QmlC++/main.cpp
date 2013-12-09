#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <crtdbg.h>

#include "OneProperty.h"
#include "List.h"
#include <hash_map>

using namespace std;

OneProperty* test()
{
	OneProperty* pTest;
	pTest = new OneProperty("TEST", 1);
	return pTest;
}

void main()
{
	void* pOneProperty = NULL;
	char* StringForPut = "HELLO";

	//TEST ONEPROPERTY-----------------------------------------
	pOneProperty = new OneProperty(StringForPut, 1);
	((OneProperty*)pOneProperty)->draw();
	
	cout << endl;
	((OneProperty*)pOneProperty)->draw();
	((OneProperty*)pOneProperty)->SetValue("OOohhh");
	cout << endl;
	((OneProperty*)pOneProperty)->draw();

	//TEST LIST-------------------------------------------
	void* pList = NULL;
	char* key = "id";
	pList = new List(key, sizeof(pOneProperty), pOneProperty);
	((List*)pList)->draw();

	//delete((List*)pList);
	delete((OneProperty*)pOneProperty);

	_CrtDumpMemoryLeaks();
	system("pause");
}
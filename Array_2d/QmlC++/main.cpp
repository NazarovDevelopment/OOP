#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <crtdbg.h>

#include "OneProperty.h"
#include "List.h"
#include "HashTable.h"
#include "QmlObject.h"

using namespace std;



void main()
 {
	//HashTable* pHash = new HashTable(1);

	QmlObject* pObject = new QmlObject(1, NULL, "_id_x_y_");

	pObject->Parse("test.txt");


	/*pHash->set("name", "vasiliy");
	pHash->set("id", "property");

	pHash->resize(2);
	
	delete(pHash);*/

	delete(pObject);
	_CrtDumpMemoryLeaks();
	system("pause");
}
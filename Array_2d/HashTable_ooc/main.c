#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include <assert.h>
#include <string.h>
#include "object.h"
#include "new.h"
#include "list_in_ht.h"
#include "HashTable_ooc.h" 

void main()
{
	struct Object* obj;
	Pointer check;
	Pointer ht;
	char *b = "123";

	obj = new(Object, 1, 1, 1);
	printf("%d\n", obj->b);
	printf("%d\n", obj->r);
	printf("%d\n", obj->g);

	ht = new(HashTable, 10, NULL);
	/*assert(ht_has(ht, b) == 0);*/

	ht_set(ht, b, obj, sizeof(Object));
	check = ht_get(ht, b);

	printf("%d\n", ((struct Object*)check)->r);
	printf("%d\n", ((struct HashTable*)ht)->table[4]->data->r);

	//assert(((struct Object*)check)->r == obj->r);
	//(ht_has(ht, b) == 1);
	//ht_delete(ht, b);
	//assert(ht_has(ht, b) == 0);
	//ht_set(ht, b, obj);
	//assert(ht_has(ht, b) == 1);
	//ht_resize(ht, 20);
	//assert(ht_has(ht, b) == 1);
	//ht_delete(ht, b);
	//assert(ht_has(ht, b) == 0);
	//delete(ht);
	//delete(obj);

	_CrtDumpMemoryLeaks();
	system("pause");
}

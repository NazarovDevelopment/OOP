#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <crtdbg.h>


void main()
{
HashTable *ht ;
int i;

ht = ht_init(3, 0, 0);

ht_set(ht, "Vasya", (Pointer)"333-45-67");
//ht_set(ht, "Vasya", (Pointer)"3333-45-67");
ht_set(ht, "Police", (Pointer)"02");

assert(ht_get(ht, "Vasya")  == "333-45-67");
assert(ht_get(ht, "Police") == "02");

assert(ht_has(ht,"Vasya"));

ht_delete(ht,"Vasya");
ht_destroy(ht);

_CrtDumpMemoryLeaks();
system("pause");
}
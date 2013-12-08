#include "HashTable_ooc.h"


typedef void *Pointer;

typedef enum COLOR { BLACK_COLOR = 1, BLUE_COLOR, RED_COLOR, GREEN_COLOR } MyColor;

struct QmlObject
{
	struct HashTable InternalHashTable;
	//Parse ParseFunction;
	char* ValidPropertiesString;

};

void MyParser(struct QmlObject* Qobject, FILE *pFile);

extern const void *QmlObject;
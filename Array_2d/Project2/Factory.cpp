#include "Factory.h"

enum form { Rect = 1, txt = 2, intxt = 3 };

int Numbers;
QmlObject** AllObject;

Factory::Factory()
{
	Numbers = 0;
	AllObject = new QmlObject*[0x100];
}

void* Factory::CreateNewObject(string &Type)
{
	int choose = 0;
	if (Type == "Rect")
	{
		choose = Rect;
	}
	if (Type == "TXT")
	{
		choose = txt;
	}
	if (Type == "INTXT")
	{
		choose = intxt;
	}

	switch (choose)
	{
	case Rect:
	{
				 AllObject[Numbers] = new Rectangle();
				 return AllObject[Numbers++];
	}
	case txt:
	{
				return 0;
	}
	case intxt:
	{
				  return 0;
	}


	default:{
				cout << endl << "I can't find this Type" << endl;
				return NULL;
	}
	}
}

void Factory::delete_All_Objects()
{
	for (int i = 0; i < Numbers; i++)
	{
		delete (QmlObject*)AllObject[i];
	}

	delete AllObject;
}
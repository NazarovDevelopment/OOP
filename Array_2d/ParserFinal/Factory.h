#pragma once
#include <string>
#include <iostream>

#include "Rectangle.h"
using namespace std;

enum form { Rect = 1, txt = 2, intxt = 3 };

class Factory
{
public:

	void* CreateNewObject(string &Type);

	static int Numbers;
	static void* AllObject[0x100];
};

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
				 Numbers++;
				 AllObject[Numbers] = new Rectangle;
				 return AllObject[Numbers];
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

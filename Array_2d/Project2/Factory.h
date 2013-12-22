#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <iostream>

#include "Rectangle.h"
#include "QmlObject.h"

using namespace std;

extern int Numbers;
extern QmlObject** AllObject;

class Factory
{
public:

	Factory(void);

	static void* CreateNewObject(string &Type);
	static void delete_All_Objects();
	/*static int Numbers;
	static void** AllObject;*/
};

#endif
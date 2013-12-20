#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <iostream>

#include "Rectangle.h"
#include "QmlObject.h"

using namespace std;


class Factory
{
public:

	Factory();

	static class QmlObject* CreateNewObject(string &Type);

	static int Numbers;
	static class QmlObject* AllObject[256];
};

#endif

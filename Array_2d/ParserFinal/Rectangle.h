#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "QmlObject.h"

using namespace std;

class QmlObject;

class Rectangle : public QmlObject
{
public:


	Rectangle(void(*Pressed)(int key));
	
	void(*KeyPressed)(int key);
	int ChildNumbers;
	void* Childs[100];
	void* Parent;
};

#endif
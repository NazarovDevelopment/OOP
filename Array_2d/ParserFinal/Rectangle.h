#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "QmlObject.h"

using namespace std;



class Rectangle : public QmlObject
{
public:


	Rectangle(void(*Pressed)(int key));
	~Rectangle()
	{

	}

	void(*KeyPressed)(int key);
	
};


#endif
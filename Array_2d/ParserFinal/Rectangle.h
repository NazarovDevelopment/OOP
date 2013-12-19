#pragma once
#include "QmlObject.h"

using namespace std;

class Rectangle: public QmlObject 
{

public:


	Rectangle(int Size = 5, HashFunction hfunc = NULL,
		char* ValidProperty = "_id_x_y_width_height_color_canBeFocused_", 
		void (*Pressed)(int key) = NULL)
		: QmlObject(Size, hfunc, ValidProperty)
	{
		KeyPressed = Pressed;
	}

	void(*KeyPressed)(int key);

	int ChildNumbers;
	void* Childs[100];
	void* Parent;
};


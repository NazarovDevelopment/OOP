#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "QmlObject.h"

using namespace std;

class TextInput : public QmlObject
{
public:

	TextInput(void(*Pressed)(int key));
	~TextInput();

	void draw()
	{


	}

	void(*KeyPressed)(int key);

};


#endif
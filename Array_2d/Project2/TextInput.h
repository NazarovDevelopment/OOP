#ifndef TextInput_H
#define TextInput_H

#include "QmlObject.h"

using namespace std;

class TextInput : public QmlObject
{
public:

	TextInput(void(*Pressed)(int key));
	~TextInput();

	void draw(sf::RenderWindow* App);

	void(*KeyPressed)(int key);

};


#endif
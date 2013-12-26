#ifndef TextInput_H
#define TextInput_H

#include "QmlObject.h"

using namespace std;

class TextInput : public QmlObject
{
public:

	TextInput();
	~TextInput();

	void draw(sf::RenderWindow* App);

	bool KeyPressed()
	{
		return 1;
	}


};


#endif
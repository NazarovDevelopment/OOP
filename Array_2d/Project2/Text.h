#ifndef mText_H
#define mText_H

#include "QmlObject.h"

using namespace std;



class mText : public QmlObject
{
public:

	mText(void(*Pressed)(int key));
	~mText();

	void draw(sf::RenderWindow* App);

	void(*KeyPressed)(int key);

};


#endif
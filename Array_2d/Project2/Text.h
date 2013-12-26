#ifndef mText_H
#define mText_H

#include "QmlObject.h"
#include <SFML\Graphics.hpp>
using namespace std;



class mText : public QmlObject
{
public:

	mText();
	~mText();

	void draw(sf::RenderWindow* App);

	bool KeyPressed()
	{
		return 1;
	}


};


#endif
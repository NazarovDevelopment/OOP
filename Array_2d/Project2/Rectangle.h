#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SFML\Graphics.hpp>
#include "QmlObject.h"

using namespace std;



class Rectangle : public QmlObject
{
public:
	
	Rectangle();
	~Rectangle();

	void draw(sf::RenderWindow* App);
	bool KeyPressed()
	{
		switch (get<int>("onkeypressed"))
		{
			case 1:
				return 0;
		default:
		return 1;
		}
	}

	void FocusDraw(sf::RenderWindow* App);
	
};


#endif
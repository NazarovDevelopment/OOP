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

	void(*KeyPressed)(int key);
	
};


#endif
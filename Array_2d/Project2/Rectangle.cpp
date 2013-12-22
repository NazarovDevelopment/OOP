#include "Rectangle.h"

Rectangle::Rectangle(void(*Pressed)(int key)) : QmlObject()
{
	KeyPressed = Pressed;
}
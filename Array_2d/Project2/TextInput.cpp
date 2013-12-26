#include "TextInput.h"
#include "Rectangle.h"
#include "TextInput.h"
#include "Text.h"

TextInput::TextInput(void(*Pressed)(int key)) : QmlObject()
{
	type = TXTIN;
	KeyPressed = Pressed;
}

void TextInput::draw(sf::RenderWindow* App)
{
	sf::Vector2f diagon(get<int>("width"), get<int>("height"));
	sf::Vector2f pos(get<int>("x"), get<int>("y"));
	sf::RectangleShape rect(diagon);
	rect.setPosition(pos);


	App->draw(rect);


	for (int i = 0; i < ChildNumbers; i++)
	{
		switch (GetType())
		{
		case RECT:
			((Rectangle*)Childs[i])->draw(App);
		case TXT:
			((mText*)Childs[i])->draw(App);
			break;
		case TXTIN:
			((TextInput*)Childs[i])->draw(App);
			break;
		default:
			break;
		}
	}
}
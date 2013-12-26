#include "Rectangle.h"
#include "TextInput.h"
#include "Text.h"

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

Rectangle::Rectangle() : QmlObject()
{
	type = RECT;
	
}

void Rectangle::draw(sf::RenderWindow* App)
{
	sf::Vector2f diagon(get<int>("width"), get<int>("height"));
	sf::Vector2f pos(get<int>("x"), get<int>("y"));
	sf::Vector2f postxt(get<int>("x") + 5, get<int>("y") + get<int>("height") - 5);

	sf::RectangleShape rect(diagon);
	
	/*sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text("Hello", font);
	text.setCharacterSize(15);*/


	sf::Color chooseColor;// = sf::Color::Black;
	string color((string)get<string>("color"));
	
	if (color == string("blue"))
		chooseColor = sf::Color::Blue;
	if (color == string("black"))
		chooseColor = sf::Color::Black;
	if (color == string("red"))
		chooseColor = sf::Color::Red;
	if (color == string("green"))
		chooseColor = sf::Color::Green;
	if (color == string("yellow"))
		chooseColor = sf::Color::Yellow;

	rect.setPosition(pos);
	rect.setFillColor(chooseColor);
	rect.setOutlineThickness(12);
	rect.setOutlineColor(sf::Color::Black);
//	text.setPosition(postxt);

	App->draw(rect);
//	App->draw(text);

	for (int i = 0; i < ChildNumbers; i++)
	{
		switch (((Rectangle*)Childs[i])->GetType())
		{
		case RECT:
			((Rectangle*)Childs[i])->draw(App);
			break;
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
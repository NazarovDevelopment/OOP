#include "Rectangle.h"
#include "TextInput.h"
#include "Text.h"

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Factory.h"
Rectangle::Rectangle() : QmlObject()
{
	type = RECT;
	
}

void Rectangle::draw(sf::RenderWindow* App)
{
	sf::Vector2f diagon(get<int>("width"), get<int>("height"));
	sf::Vector2f pos(get<int>("x"), get<int>("y"));
	sf::RectangleShape rect(diagon);
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
	if (FocussedObject == this)
	{
		rect.setOutlineColor(sf::Color::Magenta);
	}
	else
	{
		rect.setOutlineColor(chooseColor);
	}

	rect.setOutlineThickness(2);
	rect.setFillColor(chooseColor);

	App->draw(rect);
	
	if (has("text")){
		sf::Vector2f postxt(get<int>("x") + 5, get<int>("y") + 5);
		sf::Font font;
		font.loadFromFile("arial.ttf");
		sf::Text text(get<string>("text"), font);
		text.setCharacterSize(15);
		text.setPosition(postxt);
		App->draw(text);
	}


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

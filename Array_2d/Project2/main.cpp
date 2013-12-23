#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include <crtdbg.h>


#include"Parser.h"
#include "Factory.h"
#include "OneProperty.h"
#include <SFML\Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{

	Factory();
	Parser();

	ifstream file("test.txt");
	Parser::Parse(file, NULL);
	
	//sf::RenderWindow App(sf::VideoMode(800, 600), "Hello World - SFML");
		//sf::CircleShape myCircle(10);
	//myCircle.setFillColor(sf::Color::Green);
	//sf::Vector2f vector(150, 100);
	//sf::Vector2f vector2(100, 150);
	//sf::RectangleShape myRect(vector);
	//myRect.setPosition(vector2);
	//myRect.setOutlineColor(sf::Color::Black);
	//myRect.setFillColor(sf::Color::Magenta);
	//// Основной цикл
	//while (App.isOpen())
	//{
	//	// Проверяем события (нажатие кнопки, закрытие окна и т.д.)
	//	sf::Event Event;
	//	while (App.pollEvent(Event))
	//	{
	//		// если событие "закрытие окна":
	//		if (Event.type == sf::Event::Closed)
	//		{
	//			App.close();
	//			return 0;
	//		}
	//	}
		//	// очищаем экран, и заливаем его синим цветом
	//	App.clear(sf::Color(0, 0, 255));
		//	App.draw(myCircle);
	//	App.draw(myRect);
	//	// отображаем на экран
	//	App.display();
	//}

	Factory::delete_All_Objects();
	
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
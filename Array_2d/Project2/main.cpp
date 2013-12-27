#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include <crtdbg.h>


#include"Parser.h"
#include "Factory.h"
#include "OneProperty.h"
#include <SFML\Graphics.hpp>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>


#include "MouseKlick.h"
#include "Printer.h"


using namespace std;
using namespace sf;

//bool funcPrint(sf::Keyboard Key)
//{
//	switch (Key)
//	{
//	case A:
//	case (1):
//	default:
//		break;
//	}
//}

int main()
{

	Factory();
	Parser();
	MouseEvent();

	ifstream file("test.txt");
	Parser::Parse(file, NULL);
	cout << endl;

	cout << (string)AllObject[0]->get<string>("color") << endl;
	cout << (string)AllObject[1]->get<string>("color") << endl;

	sf::RenderWindow App(sf::VideoMode(1280, 1024), "Hello World - SFML");
	
			// Основной цикл
	while (App.isOpen())
	{
		// Проверяем события (нажатие кнопки, закрытие окна и т.д.)
		sf::Event Event;
		while (App.pollEvent(Event))
		{
			// если событие "закрытие окна":
			if (Event.type == sf::Event::Closed)
			{

				App.close();
				return 0;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i PressPosMouse = sf::Mouse::getPosition();
				if (!MouseEvent::mouseUser(PressPosMouse.x - App.getPosition().x, PressPosMouse.y) - App.getPosition().y)
					return 0;
			}

//			if (sf::Keyboard::isKeyPressed())
		}
			// очищаем экран, и заливаем его синим цветом
		App.clear(sf::Color(0, 0, 255));
		Printer::draw(&App);
	 	// отображаем на экран
		App.display();
	}

	Factory::delete_All_Objects();
	
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
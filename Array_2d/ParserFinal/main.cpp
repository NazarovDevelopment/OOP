﻿#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include <crtdbg.h>

#include <SFML\Graphics.hpp>

#include"Parser.h"
#include "Factory.h"
#include "OneProperty.h"
using namespace std;

int main()
{

	Factory();
	Parser();

	ifstream file("test.txt");
	Parser::Parse(file, NULL);
	
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Hello World - SFML");

//	sf::CircleShape myCircle(10);
	//myCircle.setFillColor(sf::Color::Green);

	// Основной цикл
	while (App.isOpen())
	{
		// Проверяем события (нажатие кнопки, закрытие окна и т.д.)
		sf::Event Event;
		while (App.pollEvent(Event))
		{
			// если событие "закрытие окна":
			if (Event.type == sf::Event::Closed)
				App.close();
		}

		// очищаем экран, и заливаем его синим цветом
		App.clear(sf::Color(0, 0, 255));

	//	App.draw(myCircle);
		// отображаем на экран
		App.display();
	}

	Factory::delete_All_Objects();
	
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
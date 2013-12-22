#include <iostream>
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

	
	cout << AllObject[1]->get<int>("x") << endl;

   // cout <<(string)(((QmlObject*)AllObject[0])->get("id")) << endl;
	/*
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Hello World - SFML");

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

		// отображаем на экран
		App.display();
	}

	*/

	Factory::delete_All_Objects();
	
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
#include <iostream>
#include <string>
#include <fstream>

#include <crtdbg.h>

#include"Parser.h"
#include "Factory.h"


void main()
{
	/*Factory();
	Parser();

	ifstream file("test.txt");
	Parser::Parse(file, NULL);



	Factory::delete_All_Objects();*/


	int value = Char_To_int("1234566");
	
	_CrtDumpMemoryLeaks();
	system("pause");
}
#include <iostream>
#include <string>
#include <fstream>

#include"Parser.h"
#include "Factory.h"


void main()
{
	Factory();
	Parser();

	ifstream file("test.txt");
	Parser::Parse(file);




	system("pause");

}
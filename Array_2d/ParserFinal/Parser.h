#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

#include "QmlObject.h"
#include "Factory.h"
using namespace std;


class Parser
{
public:
	static void Parse(ifstream &file, QmlObject* MainObject);
private:
};

int Miss_All_Space(char* buffer, int* i);

#endif
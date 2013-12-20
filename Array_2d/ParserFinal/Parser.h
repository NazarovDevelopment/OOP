#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

#include "Factory.h"
using namespace std;


class Parser
{
public:
	static void Parse(ifstream &file);
private:
};

int Miss_All_Space(char* buffer, int* i);


#endif
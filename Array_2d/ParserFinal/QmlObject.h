#ifndef QMLOBJECT_H
#define QMLOBJECT_H

#include <string>
#include <fstream>
#include <iostream>

#include "HashTable.h"
#include "Parser.h"
#include "Factory.h" 

using namespace std;

class QmlObject : public HashTable
{
public:
	QmlObject();
	QmlObject(size_t ArraySize);
	QmlObject(size_t ArraySize, HashFunction hfunc);
	QmlObject(size_t ArraySize, HashFunction hfunc, char* ValidString);
	~QmlObject();

public:

	void Parse(ifstream &file);

private:
	char* ValidPropertiesString;
};

#endif
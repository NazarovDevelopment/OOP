#ifndef QMLOBJECT_H
#define QMLOBJECT_H

#include <string>
#include <fstream>
#include <iostream>

#include <SFML\Graphics.hpp>
#include "HashTable.h"

typedef enum _TypeObject {RECT = 1, TXT = 2, TXTIN = 3} TYPE ;

class QmlObject : public HashTable
{
public:
	QmlObject();
	QmlObject(size_t ArraySize);
	QmlObject(size_t ArraySize, HashFunction hfunc);
	QmlObject(size_t ArraySize, HashFunction hfunc, char* ValidString);
	~QmlObject();

public:
	
	void AddChild(QmlObject* NextChild);
	void AddParent(QmlObject* NewParent);
	void Parse(ifstream &file, int count);
	TYPE GetType()
	{
		return type;
	}
protected:
	
	TYPE type;
	int ChildNumbers;
	QmlObject* Childs[100];
	void* Parent;
	char* ValidPropertiesString;
};

#endif
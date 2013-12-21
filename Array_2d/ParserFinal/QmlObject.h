#ifndef QMLOBJECT_H
#define QMLOBJECT_H

#include <string>
#include <fstream>
#include <iostream>

#include "HashTable.h"

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
	void Parse(ifstream &file);

private:
	int ChildNumbers;
	void* Childs[100];
	void* Parent;
	char* ValidPropertiesString;
};

#endif
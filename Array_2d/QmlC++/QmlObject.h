#pragma once

#include "HashTable.h"

class QmlObject : public HashTable
{
public:
	QmlObject();
	QmlObject(size_t ArraySize);
	QmlObject(size_t ArraySize, HashFunction hfunc);
	QmlObject(size_t ArraySize, HashFunction hfunc, char* ValidString);
	~QmlObject();

private:
	char* ValidPropertiesString;
};

QmlObject::QmlObject(size_t ArraySize) :HashTable(ArraySize)
{
	ValidPropertiesString = "_type_id_";
}

QmlObject::QmlObject(size_t ArraySize, HashFunction hfunc) : HashTable(ArraySize, hfunc)
{
	ValidPropertiesString = "_type_id_";
}

QmlObject::QmlObject(size_t ArraySize, HashFunction hfunc, char* ValidString) : HashTable(ArraySize, hfunc)
{
	ValidPropertiesString = ValidString;
}

QmlObject::~QmlObject()
{
	delete(ValidPropertiesString);
}


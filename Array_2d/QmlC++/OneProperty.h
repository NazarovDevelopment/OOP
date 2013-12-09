#pragma once
#include <string>
#include <iostream>

using namespace std;
#pragma warning(disable : 4996)

class OneProperty
{
public:
	OneProperty();
	OneProperty(void* PutValue, bool ItIsInt);
	OneProperty(OneProperty &a)
	{
		value = calloc(strlen((char*)a.value),sizeof(char));
		strcpy((char*)value, (char*)a.value);
	}
	~OneProperty();

public:
	void draw();
	void SetValue(void* data);
	void* GetValue();

	
private:
	void* value;
};

OneProperty::OneProperty()
{
	value = 0;
}

OneProperty::OneProperty(void* PutValue, bool ItIsInt)
{
	//value = new char;
	//memcpy(value, PutValue, sizeof(char)*strlen((char*)PutValue));
	value = PutValue;
}

OneProperty::~OneProperty()
{
	//free((char*)value);
	
}

void OneProperty::draw()
{
	if (value)
	{
		cout << (char*)value << endl;
	}
}

void OneProperty::SetValue(void* data)
{
	if (data)
	{
		value = (char*)data;
	}
}

void* OneProperty::GetValue()
{
	return value;
}
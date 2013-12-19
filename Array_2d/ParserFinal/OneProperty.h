#pragma once
#include <string>
#include <iostream>

using namespace std;
#pragma warning(disable : 4996)

class OneProperty
{
public:
	OneProperty();
	OneProperty(void* PutValue, int size);
	~OneProperty();

public:
	void draw();
	void SetValue(void* data);
	void* GetValue();

	
private:
	void* value;
};

class b  : public OneProperty
{

	void draw()
	{

	}
private:
	int size;
};

OneProperty::OneProperty()
{
	value = 0;
}

OneProperty::OneProperty(void* PutValue, int size)
{
	value = new char[size+1];
	memcpy(value, PutValue, sizeof(char)*(size+1));
	//value = PutValue;
}

OneProperty::~OneProperty()
{
	delete value;
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
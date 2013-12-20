#ifndef ONEPROPERTY_H
#define ONEPROPERTY_H

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

#endif
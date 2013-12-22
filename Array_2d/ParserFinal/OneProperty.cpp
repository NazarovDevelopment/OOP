#include "OneProperty.h"

using namespace std;

OneProperty::OneProperty()
{
	value = 0;
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

IDataWrapper* OneProperty::GetValue()
{
	return value;
}
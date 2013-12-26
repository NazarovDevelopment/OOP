#ifndef ONEPROPERTY_H
#define ONEPROPERTY_H

#include <string>
#include <iostream>

#pragma warning(disable : 4996)
using namespace std;

class IDataWrapper {
public:
	virtual operator const int() const = 0;
	virtual operator const string() const = 0;

	virtual IDataWrapper* clone() const = 0;
};

class IntWrapper : public IDataWrapper {
private:
	int _data;
public:
	IntWrapper(const int &value) : _data(value) {}
	operator const int() const {
		return _data;
	}
	operator const string() const {
		throw exception("ty ");
	}

	IDataWrapper* clone() const {
		return new IntWrapper(_data);
	}
};

class StringWrapper : public IDataWrapper {
private:
	string _data;
public:
	StringWrapper(const string &value) : _data(value) {}
	operator const string() const {
		return _data;
	}
	operator const int() const {
		throw exception("ty");
	}
	IDataWrapper* clone() const {
		return new StringWrapper(_data);
	}
};
class OneProperty final
{
public:
	OneProperty();
	//OneProperty<int>(void* PutValue, int size);
	OneProperty(const int &value) {
		this->value = new IntWrapper(value);
	}
	OneProperty(const string &value) {
		this->value = new StringWrapper(value);
	}
	OneProperty(const IDataWrapper &value) {
		this->value = value.clone();
	}
	~OneProperty();

public:
	void draw();
	//void SetValue(_T &data);
	IDataWrapper* GetValue();


private:
	IDataWrapper* value;
};

#endif
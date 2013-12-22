#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "OneProperty.h"

using namespace std;
#pragma warning(disable : 4996)


class List
{
public:
	List();
	List(char* Putkey, const int &PutValue);
	List(char* Putkey, const string &PutValue);

	~List();

public:
	void draw();
	void SetNext(List* pList);

	void SetData(const int &value);
	void SetData(const string &value);
	void SetData(const IDataWrapper &wrapper);

	void foreach(void(*f)(char *key, void* data));

	List* prepend(char* key, const string &value);
	List* prepend(char* key, const int &value);


	char* Getkey();
	bool has(char* key);

public:
	OneProperty* data;
	List* next;

private:
	char*key;
	
};

#endif
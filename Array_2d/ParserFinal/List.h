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
	List(char* Putkey, void* Putdata, int size);
	~List();

public:
	void draw();
	void SetNext(List* pList);
	void SetData(void* value, int size);
	void foreach(void(*f)(char *key, void* data));

	List* prepend(char* key, void* Putdata, int size);

	char* Getkey();
	bool has(char* key);

public:
	OneProperty* data;
	List* next;

private:
	char*key;
	
};

#endif
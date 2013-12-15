#pragma once

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
	List(char* Putkey, void* Putdata);
	~List();

public:
	void draw();
	void SetNext(List* pList);
	void SetData(void* value);

	List* prepend(char* key, void* Putdata);

	char* Getkey();

public:
	OneProperty* data;
	List* next;

private:
	char*key;
	
};

List::List()
{
	key = NULL;
	data = NULL;
}

List::List(char* Putkey, void* PutValue)
{
	//key = (char*)calloc(strlen(Putkey) + 1, sizeof(char));
	data = new OneProperty(PutValue);
			
	key = new char[strlen(Putkey)+1];//(char*)calloc(strlen(Putkey) + 1, sizeof(char));
	strcpy(key, Putkey);
	next = NULL;
}

List::~List()
{
	List* pList = this;

	if (pList->next)
	{
		delete(pList->next);
	}

	delete(data);
	delete(key);
	
}

void List::draw()
{
	List* ForDraw = this;
		
	while (ForDraw)
	{
		cout << endl;
		(ForDraw->data)->draw();
		ForDraw = ForDraw->next;
		cout << endl;
	}

	cout << endl;
}

void List::SetNext(List* pList)
{
	next = pList;
}

List* List::prepend(char* key, void* Putdata)
{
	List* new_list = new List(key, Putdata); 
	//new_list->SetNext(this);
	new_list->next = this;
	return new_list;
}

char* List::Getkey()
{
	return key;
}

void List::SetData(void* value)
{
	OneProperty* pOProp = new OneProperty(value);

	data = pOProp;
}
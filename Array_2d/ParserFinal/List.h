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

List::List()
{
	key = NULL;
	data = NULL;
}

List::List(char* Putkey, void* PutValue, int size)
{
	//key = (char*)calloc(strlen(Putkey) + 1, sizeof(char));
	data = new OneProperty(PutValue, size);
			
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

List* List::prepend(char* key, void* Putdata, int size)
{
	List* new_list = new List(key, Putdata, size); 
	//new_list->SetNext(this);
	new_list->next = this;
	return new_list;
}

char* List::Getkey()
{
	return key;
}

void List::SetData(void* value, int size)
{
	OneProperty* pOProp = new OneProperty(value, size);

	data = pOProp;
}

bool List::has(char* key)
{
	List* list = this;
	while (list != NULL)
	{
		if (strcmp(list->key, key) == 0)
		{
			return 1;
		}
		list = list->next;
	}
	return 0;
}

void  List::foreach(void(*f)(char *Putkey, void* Putvalue))
{
	List* list = this;
	while (list != NULL)
	{
		f(list->key, list->data->GetValue());
		list = list->next;
	}
}

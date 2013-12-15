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
	List(char* Putkey, size_t size, void* Putdata);
	~List();

public:
	void draw();

private:
	char*key;
	size_t SizeData;
	void* data;
	
	List* next;
};

List::List()
{
	key = NULL;
	SizeData = 0;
	data = NULL;
}

List::List(char* Putkey, size_t size, void* Putdata)
{
	SizeData = size;
	//key = (char*)calloc(strlen(Putkey) + 1, sizeof(char));
	
	
		
	key = (char*)calloc(strlen(Putkey) + 1, sizeof(char));
	strcpy(key, Putkey);
	next = NULL;
}

List::~List()
{
	delete(data);
	free(key);
	
}

void List::draw()
{
	List* ForDraw = this;
	cout << endl;
	cout << endl;
		
	while (ForDraw)
	{
		cout << endl;
		((OneProperty*)ForDraw->data)->draw();
		ForDraw = ForDraw->next;
		cout << endl;
	}

	cout << endl;
}
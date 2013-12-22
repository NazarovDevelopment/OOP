#include "List.h"

List::List()
{
	key = NULL;
	data = NULL;
}

List::List(char* Putkey, const int &PutValue)
{
	//key = (char*)calloc(strlen(Putkey) + 1, sizeof(char));
	data = new OneProperty(PutValue);

	key = new char[strlen(Putkey) + 1];//(char*)calloc(strlen(Putkey) + 1, sizeof(char));
	strcpy(key, Putkey);
	next = NULL;
}

List::List(char* Putkey, const string &PutValue)
{
	//key = (char*)calloc(strlen(Putkey) + 1, sizeof(char));
	data = new OneProperty(PutValue);

	key = new char[strlen(Putkey) + 1];//(char*)calloc(strlen(Putkey) + 1, sizeof(char));
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

List* List::prepend(char* key, const int &Putdata)
{
	List* new_list = new List(key, Putdata);
	//new_list->SetNext(this);
	new_list->next = this;
	return new_list;
}
List* List::prepend(char* key, const string &Putdata)
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

void List::SetData(const int &value)
{
	OneProperty* pOProp = new OneProperty(value);

	data = pOProp;
}
void List::SetData(const std::string &value)
{
	OneProperty* pOProp = new OneProperty(value);

	data = pOProp;
}
void List::SetData(const IDataWrapper &value) {
	data = new OneProperty(value);
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

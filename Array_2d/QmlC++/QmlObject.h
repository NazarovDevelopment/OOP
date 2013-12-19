#pragma once
#include <string>
#include <fstream>
#include "HashTable.h"

using namespace std;

class QmlObject : public HashTable
{
public:
	QmlObject();
	QmlObject(size_t ArraySize);
	QmlObject(size_t ArraySize, HashFunction hfunc);
	QmlObject(size_t ArraySize, HashFunction hfunc, char* ValidString);
	~QmlObject();

public:

	void Parse(const string &FileName);

private:
	char* ValidPropertiesString;
};

QmlObject::QmlObject(size_t ArraySize) :HashTable(ArraySize)
{
	ValidPropertiesString = "_type_id_";
}
QmlObject::QmlObject(size_t ArraySize, HashFunction hfunc) : HashTable(ArraySize, hfunc)
{
	ValidPropertiesString = "_type_id_";
}
QmlObject::QmlObject(size_t ArraySize, HashFunction hfunc, char* ValidString) : HashTable(ArraySize, hfunc)
{
	ValidPropertiesString = ValidString;
}
QmlObject::~QmlObject()
{
	
}
int Miss_All_Space(char* buffer, int* real_number)
{
	int i = *real_number;

	if (!isspace(buffer[i]))
	{
		return i;
	}

	while (buffer[i + 1] == ' ')
		i++;
	*real_number = i++;
	return i++;
}

void QmlObject::Parse(const string &FileName)
{
	char* buffer = new char[0x100];
	char* name = new char[20];
	char* value = new char[20];
	char* _name = new char[20];
	
	bool flag_name = 0;
	bool flag_value = 0;
	int i = 0;
	int j = 0;
	
	ifstream file(FileName);
	if (!file.is_open())
		return;
	
	while (!file.eof()) {
		file.getline(buffer, 0x100 * sizeof(char), '\n');
		Miss_All_Space(buffer, &i);
		if (buffer[i] == '{')
		{
			i++;
			Miss_All_Space(buffer,&i);
			i = 0;
			continue;
		}

		if (buffer[i] == '}')
		{
				printf("\nEND OF FILE\n");
				break;
		}

  		while (!isspace(buffer[i]))
		{
			if (buffer[i] != ':')
			{
				name[j++] = buffer[i++];
			}
			else
			{
				name[j] = '\0';
				break;
			}
		}

		Miss_All_Space(buffer, &i);
		
		if (buffer[i] == ':')
		{
			flag_name = 1;
			i++;
			Miss_All_Space(buffer, &i);
		}
		else
		{
			
			printf("\n This file contain ERROR\n");
			delete(buffer);
			delete(name);
			delete(_name);
			delete(value);
			return;
		}
		
		if (flag_name && strstr(ValidPropertiesString, name))
		{
			Miss_All_Space(buffer, &i);
			j = 0;
			Miss_All_Space(buffer, &i);
			i++;
			while (1)
			{
				if (!isspace(buffer[i]) && buffer[i]!='\0' && buffer[i] != '\n')
				{
					value[j++] = buffer[i++];
				}
				else
				{
  					break;
				}
			}
			
			value[j] = '\0';
			flag_value = 1;
		}

		if (flag_name && flag_value && name && value)
		{
			this->set(name, value, sizeof(char)*strlen(value));
		}
		else
		{
			printf("ERROR");
		}

		i = j = 0;
	}
	delete(buffer);
	delete(name);
	delete(_name);
	delete(value);

}

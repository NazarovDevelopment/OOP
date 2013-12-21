#include "QmlObject.h"
#include "Parser.h"




QmlObject::QmlObject() :HashTable(5)
{
	ValidPropertiesString = "_id_x_y_color_width_height_";
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

void QmlObject::AddChild(QmlObject* NextChild)
{
	Childs[ChildNumbers] = NextChild;
	ChildNumbers++;
}

void QmlObject::AddParent(QmlObject* NewParent)
{
	Parent = NewParent;
}

int Miss_All_Space(char* buffer, int* real_number)
{
	int i = *real_number;

	if (!isspace(buffer[i]))
	{
		return i;
	}

	while (buffer[i + 1] == ' ' || buffer[i + 1] == '\t')
		i++;
	*real_number = i + 1;
	return i++;
}

void QmlObject::Parse(ifstream &file)
{
 	char* buffer = new char[0x100];
	char* name = new char[20];
	char* value = new char[20];
	char* _name = new char[20];

	fstream::pos_type PrevPos;
	fstream::pos_type NewPos;

	bool flag_name = 0;
	bool flag_value = 0;
	int i = 0;
	int j = 0;



 	while (!file.eof()) {
		PrevPos = file.tellg();
		file.getline(buffer, 0x100 * sizeof(char), '\n');
		Miss_All_Space(buffer, &i);
		if (buffer[i] == '\0')
		{
			cout << endl << "Line is Empty" << endl;
			i = 0;
			continue;
		}

		if (buffer[i] == '{')
		{
			file.seekg(NewPos);
			Parser::Parse(file, this);
			i = 0;
			j = 0;
			continue;
		}

		if (buffer[i] == '}')
		{
			delete(buffer);
			delete(_name);
			delete(name);
			delete(value);
			return;
		}

		if (buffer[i] != ' ')
		{
			while (!isspace(buffer[i]) && buffer[i] != '\0')
			{
				name[j++] = buffer[i++];
			}

			name[j] = '\0';
			flag_name = 1;

			Miss_All_Space(buffer, &i);
			if (buffer[i] != ':')
			{
				NewPos = PrevPos;
				Miss_All_Space(buffer, &i);
				if (buffer[i] == '\0')
				{
					i = 0;
					continue;
				}
				if (buffer[i] == '{')
				{
					file.seekg(PrevPos);
					Parser::Parse(file, this);
					i = 0;
					j = 0;
					continue;
				}
			}
			if (buffer[i] == ':' && flag_name && strstr(ValidPropertiesString, name))
			{
				i++;
				j = 0;
				Miss_All_Space(buffer, &i);
				while (!isspace(buffer[i]) && buffer[i]!= '\0')
				{
					value[j++] = buffer[i++];
				}
				value[j] = '\0';
				set(name, value, strlen(value));
			}


		}
		i = j = 0;

	}
	delete(buffer);
	delete(_name);	
	delete(name);
	delete(value);

}

#include "QmlObject.h"
#include "Parser.h"

#define rangeCheck(x, a, b) (x >= a && x <= b)


QmlObject::QmlObject() :HashTable(5)
{
	ValidPropertiesString = "_id_x_y_color_width_height_onkeypressed_canbefocussed_text_";
	for (int i = 0; i < 100; i++){
		Childs[i] = NULL;
	}
}
QmlObject::QmlObject(size_t ArraySize, HashFunction hfunc) : HashTable(ArraySize, hfunc)
{
	ValidPropertiesString = "_type_id_";
	for (int i =0 ; i < 100; i++){
		Childs[i] = NULL;
	}
}
QmlObject::QmlObject(size_t ArraySize, HashFunction hfunc, char* ValidString) : HashTable(ArraySize, hfunc)
{
	ValidPropertiesString = ValidString;
	for (int i =0 ; i < 100; i++){
		Childs[i] = NULL;
	}
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

int Char_To_int(char* string)
{
	int Value = 0;
	int len = strlen(string);

	for (int i = 0; i < len; i++)
	{
		switch (string[i])
		{
		case '0':
			break;;
		case '1':
			Value = Value + 1 * pow(10, len - i - 1);
			break;
		case '2':
			Value = Value + 2 * pow(10, len - i - 1);
			break;
		case '3':
			Value = Value + 3 * pow(10, len - i - 1);
			break;
		case '4':
			Value = Value + 4 * pow(10, len - i - 1);
			break;
		case '5':
			Value = Value + 5 * pow(10, len - i - 1);
			break;
		case '6':
			Value = Value + 6 * pow(10, len - i - 1);
			break;
		case '7':
			Value = Value + 7 * pow(10, len - i - 1);
			break;
		case '8':
			Value = Value + 8 * pow(10, len - i - 1);
			break;
		case '9':
			Value = Value + 9 * pow(10, len - i - 1);
			break;

		default:
			cout << "ERROR" << endl;
			return 0;
		}
	}

	return Value;
}

void QmlObject::Parse(ifstream &file, int count)
{
  	char* buffer = new char[0x100];
	char* name = new char[20];
	char* _name = new char[20];
	char* value = new char[20];
	char* _value = new char[20];

	fstream::pos_type PrevPos;
	fstream::pos_type NewPos;

	bool flag_name  = false;
	bool flag_value = false;
	int i = count;
	int j = 0;

	PrevPos = file.tellg();
	file.getline(buffer, 256, '\n');
	Miss_All_Space(buffer, &i);

		while (true)
		{
			Miss_All_Space(buffer, &i);

			if (buffer[i] == '}')
			{
				delete(buffer);
				delete(_name);
				delete(name);
				delete(value);
				delete(_value);
				return;
			}

			if (!isspace(buffer[i]) && buffer[i] != '\0' && buffer[i] != '\n' && buffer[i] != ';'&& buffer[i] != ':'
				&& !flag_name && !flag_value)
			{
				NewPos = PrevPos;
				while (!isspace(buffer[i]) && buffer[i] != '\0' &&buffer[i] != '\n' && buffer[i] != ':' && buffer[i] != ';'
					&& buffer[i] != '{')
				{
					name[j++] = buffer[i++];
				}
				name[j] = '\0';
				j = 0;
				flag_name = true;
			}
			
 			Miss_All_Space(buffer, &i);
			if (buffer[i] == '\0')
			{
				PrevPos = file.tellg();
				file.getline(buffer, 256, '\n');
				i = j = 0;
				continue;
			}

			if (!flag_name && !flag_value && buffer[i] == ';')
			{

				PrevPos = file.tellg();
				file.getline(buffer, 256, '\n');
				i = j = 0;
				continue;
			}
			if (buffer[i] == ':')
			{
				flag_value = true;
				i++;
			}
			if (!flag_value && flag_name && buffer[i] == ';')
			{

			}
			Miss_All_Space(buffer, &i);
			if (buffer[i] == '\0' && flag_value)
			{
				PrevPos = file.tellg();
				i = j = 0;
				file.getline(buffer, 256, '\n');
				continue;
			}

			if (buffer[i] == '{' && flag_name && !flag_value)
			{
				file.seekg(NewPos);
				Parser::Parse(file, this);
				i = j = 0;
				flag_name = flag_value = false;
				PrevPos = file.tellg();
				file.getline(buffer, 256, '\n');
				continue;
			}
			
			Miss_All_Space(buffer, &i);

			if (!isspace(buffer[i]) && buffer[i] != '\0' && buffer[i] != '\n' && flag_name && flag_value)
			{
				while (!isspace(buffer[i]) && buffer[i] != '\0' && flag_name && buffer[i] != '\n'&& buffer[i] != ';' && buffer[i] != '}')
				{
					value[j++] = buffer[i++];
				}
   				value[j] = '\0';
				flag_value = false;

				if (strstr(ValidPropertiesString, name))
				{
					if (value[0] == '\"' && value[strlen(value) - 1] == '\"')
					{
						int k = 1;
						j = 0;
						while (value[k] != '\"')
						{
							_value[j++] = value[k++];
						}
						_value[j] = '\0';
						k = j = 0;
						set(name, _value);
					}
					else
					{
						int INTvalue = Char_To_int(value);
						set(name, INTvalue);
					}
					
					Miss_All_Space(buffer, &i);
					if (buffer[i] == '\0')
					{
						i = j = 0;
						flag_name = flag_value = false;
						PrevPos = file.tellg();
						file.getline(buffer, 256, '\n');
						continue;
					}
					if (buffer[i] == ';')
					{
						j = 0;
						flag_name = flag_value = false;
						i++;
						continue;
					}
					if (!isspace(buffer[i]) && buffer[i] != '\0' && buffer[i] != '\n')
					{
						j = 0;
						flag_name = flag_value = false;
						continue;
					}
				}
			}
			i = j = 0;
	}

 	/*while (!file.eof()) {
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
			delete(_value);
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

				if (value[0] == '\"' && value[strlen(value)-1] == '\"')
				{
					int k = 1;
					j = 0;
					while (value[k] != '\"')
					{
						_value[j++] = value[k++];
					}
					_value[j] = '\0';
					set(name, _value);
				}
				else
				{
					int INTvalue = Char_To_int(value);
					set(name,  INTvalue);
				}
			}


		}
		i = j = 0;

	}*/
	delete(buffer);
	delete(_name);	
	delete(name);
	delete(value);
	delete(_value);

}

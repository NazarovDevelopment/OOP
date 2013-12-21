#include "Parser.h"
#include "QmlObject.h"
#include <math.h>

void Parser::Parse(ifstream &file, QmlObject* MainObject)
{
	char* buffer = new char[0x100];
	char* name = new char[20];
	char* type = new char[20];


	int i = 0;
	int j = 0;

	bool FlagType = 0;


	while (!file.eof()) {
		file.getline(buffer, 0x100 * sizeof(char), '\n');

		Miss_All_Space(buffer, &i);

		if (buffer[i] == '\}')
			break;
		
		if (buffer[i] == '\0' )
		{
			printf("Line is Empty");
			continue;
		}

		if (buffer[i] != ' ' && buffer[i] != '\0' && FlagType == 0)
		{
			while (!isspace(buffer[i]) && buffer[i] != '\n' && buffer[i] != '\0')
			{
				name[j++] = buffer[i++];
			}
			name[j] = '\0';
			FlagType = 1;
			Miss_All_Space(buffer, &i);
		}

		if (buffer[i] == '{' && FlagType == 1)
		{
			j = 0;

			while (name[j] != '_')
			{
				type[j] = name[j];
				j++;
			}
			type[j] = '\0';
			j = 0;

			QmlObject* new_Qmlobject;
			new_Qmlobject = (QmlObject*) Factory::CreateNewObject((string)type);
			
			new_Qmlobject->AddParent(MainObject);
			if (MainObject != 0)
			{
				MainObject->AddChild(new_Qmlobject);
			}
			new_Qmlobject->Parse(file);
			FlagType = false;
		}
		else
		{
			if (buffer[i] == '\0')
			{
				i = 0;
				continue;
			}
			else
			{
				cout << endl << "ERROR IN THIS FILE" << endl;
			}
		}




	}
	delete(buffer);
	delete(name);
	delete(type);
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
			continue;
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

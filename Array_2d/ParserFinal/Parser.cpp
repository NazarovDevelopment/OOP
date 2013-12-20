#include "Parser.h"
#include "QmlObject.h"

void Parser::Parse(ifstream &file)
{
	char* buffer = new char[0x100];
	char* name = new char[20];

	int i = 0;
	int j = 0;

	bool FlagType = 0;


	while (!file.eof()) {
		file.getline(buffer, 0x100 * sizeof(char), '\n');

		Miss_All_Space(buffer, &i);

		if (buffer[i] = '\0')
		{
			printf("Line is Empty");
			continue;
		}

		if (buffer[i] != ' ' && buffer[i] != '\0' && FlagType == 0)
		{
			while (!isspace(buffer[i]))
			{
				name[j++] = buffer[i++];
			}
			name[j] = '\0';
			FlagType = 1;
			Miss_All_Space(buffer, &i);
		}

		if (buffer[i] == '{' && FlagType == 1)
		{
			QmlObject* new_Qmlobject;
			new_Qmlobject = Factory::CreateNewObject((string)name);
			new_Qmlobject->Parse(file);
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
}

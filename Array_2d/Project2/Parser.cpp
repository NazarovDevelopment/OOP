#include "Parser.h"
#include "QmlObject.h"

#include <math.h>
void Parser::Parse(ifstream &file, QmlObject* MainObject)
{
	char* buffer = new char[256];
	char* name = new char[256];
	char* type = new char[256];
	
	int index = 0;
	int i = 0, j = 0;
	bool FlagType = 0;

	ifstream::pos_type NowPos;

	while (!file.eof())
	{
		j = i = index = 0;
	
		NowPos = file.tellg();
		file.getline(buffer, 256, '\n');
		Miss_All_Space(buffer, &i);

		if (buffer[i] == '\n')
			continue;

		if (isspace(buffer[i]) && buffer[i] != '\n')
		{
			while (isspace(buffer[i]) && buffer[i] != '\n')
			{
				name[j++] = buffer[i++];
			}
			name[j] = '\0';
		}

		Miss_All_Space(buffer, &i);

		while (true)
		{
			if (buffer[i] == '{')
			{
				Miss_All_Space(buffer, &i);
				while (true)
				{
					QmlObject* new_Qmlobject;
					new_Qmlobject = (QmlObject*)Factory::CreateNewObject((string)name);

					new_Qmlobject->AddParent(MainObject);
					if (MainObject != 0)
					{
						MainObject->AddChild(new_Qmlobject);
					}
					Miss_All_Space(buffer, &i);
					if (buffer[i] != '\0')
					{
						file.seekg(NowPos);
						QmlObject* new_Qmlobject;
						new_Qmlobject = (QmlObject*) Factory::CreateNewObject((string)name);
							
						new_Qmlobject->AddParent(MainObject);
						if (MainObject != 0)
							{
									MainObject->AddChild(new_Qmlobject);
							}
						new_Qmlobject->Parse(file, i);
						FlagType = false;
						i = 0; j = 0; continue;
					}
					else
					{

					}
				}
			}
		}

	}

}
//void Parser::Parse(ifstream &file, QmlObject* MainObject)
//{
//	char* buffer = new char[0x100];
//	char* name = new char[20];
//	char* type = new char[20];
//
//
//	int i = 0;
//	int j = 0;
//
//	bool FlagType = 0;
//
//
//	while (!file.eof()) {
//		file.getline(buffer, 0x100 * sizeof(char), '\n');
//
//		Miss_All_Space(buffer, &i);
//
//		if (buffer[i] == '\}')
//			break;
//		
//		if (buffer[i] == '\0' )
//		{
//			printf("Line is Empty");
//			continue;
//		}
//
//		if (buffer[i] != ' ' && buffer[i] != '\0' && FlagType == 0)
//		{
//			while (!isspace(buffer[i]) && buffer[i] != '\n' && buffer[i] != '\0')
//			{
//				name[j++] = buffer[i++];
//			}
//			name[j] = '\0';
//			FlagType = 1;
//			Miss_All_Space(buffer, &i);
//		}
//
//		if (buffer[i] == '{' && FlagType == 1)
//		{
//			j = 0;
//
//			while (name[j] != '_')
//			{
//				type[j] = name[j];
//				j++;
//			}
//			type[j] = '\0';
//			j = 0;
//
//			QmlObject* new_Qmlobject;
//			new_Qmlobject = (QmlObject*) Factory::CreateNewObject((string)type);
//			
//			new_Qmlobject->AddParent(MainObject);
//			if (MainObject != 0)
//			{
//				MainObject->AddChild(new_Qmlobject);
//			}
//			new_Qmlobject->Parse(file);
//			FlagType = false;
//		}
//		else
//		{
//			if (buffer[i] == '\0')
//			{
//				i = 0;
//				continue;
//			}
//			else
//			{
//				cout << endl << "ERROR IN THIS FILE" << endl;
//			}
//		}
//
//
//
//
//	}
//	delete(buffer);
//	delete(name);
//	delete(type);
//}


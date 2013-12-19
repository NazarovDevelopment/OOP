#pragma once
#include <string>
#include <fstream>

using namespace std;

class Parser
{
public:
	static void Parse(const string &filename);
private:
};

class QMLObject
{


public:
	virtual void Parse();
};

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

void Parser::Parse(const string &filename)
{
	char* buffer = new char[0x100];
	char* name = new char[20];
	
	ifstream file(filename);

	int i = 0;
	int j = 0;

	if (!file.is_open())
		return;
	
	
	while (!file.eof()) {
		file.getline(buffer, 0x100 * sizeof(char), '\n');
		
		Miss_All_Space(buffer, &i);
		
		if (buffer[i] = '\0')
		{
			printf("Line is Empty");
			continue;
		}
		
		if (buffer[i] != ' ' && buffer[i] != '\0')
		{
			while (!isspace(buffer[i]))
			{
				name[j++] = buffer[i++];
			}
			name[j] = '\0';
			Miss_All_Space();
		}
		
		


	}
}


#include <fstream>
#include <string>
#include "ConfigurationFile.h"

using namespace std;

ConfigurationFile* ConfigurationFile::ConfigFile = new ConfigurationFile();

ConfigurationFile::ConfigurationFile()
{

}

ConfigurationFile::~ConfigurationFile()
{

}

ConfigurationFile& ConfigurationFile::Instance()
{
	return *ConfigFile;
}

void ConfigurationFile::Set(string key, string value)
{
	ofstream file;
	file = ofstream("config.txt", ios::app);
	//file.seekg(file.end);
	string sentence = key + ' ' + value;
	file << sentence << endl;
	file.close();
}

bool ConfigurationFile::Find(const string key)
{
	ifstream file;
	file = ifstream("config.txt", ios::in);
	while (!file.eof())
	{
		char str[256];
		file.getline(str, 256);
		string line = str;
		if (key == line.substr(line.find_first_not_of(" "), line.find_first_of(" ", line.find_first_not_of(" "))))
		{
			return true;
		}
		line.clear();
	}
	return false;
}

string ConfigurationFile::GetValue(const string key)
{
	if (!Find(key))
		return 0;
	ifstream file;
	file = ifstream("config.txt", ios::in);
	string value;

	while (!file.eof())
	{
		char str[256];
		file.getline(str, 256);
		string line = str;
		if (key == line.substr(line.find_first_not_of(" "), line.find_first_of(" ", line.find_first_not_of(" "))))
		{
			value = line.substr(line.find_first_not_of(" ", key.length() + line.find_first_not_of(" ")),
				line.find_first_of(" ", line.find_first_not_of(" ", key.length() + line.find_first_not_of(" "))));
			return value;
		}
		line.clear();
	}
}

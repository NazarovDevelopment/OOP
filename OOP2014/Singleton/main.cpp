#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "ConfigurationFile.h"

using namespace std;



void main()
{
	string str("3");
	bool abool = ConfigurationFile::Instance().Find(str);
	string value = ConfigurationFile::Instance().GetValue(str);

	system("pause");
}
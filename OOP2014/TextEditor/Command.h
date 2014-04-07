#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Document
{
	vector<string> data;

public:
	void Insert(int line, const string& str)
	{
		if (line <= data.size())
			data.insert(data.begin() + line, str);
		else
			cout << "Error!" << endl;
	}
	
	void Remove(int line)
	{
		if (!(line > data.size()))
			data.erase(data.begin() + line);
		else
			cout << "Error!" << endl;
	}

	string& operator [] (int x)
	{
		return data[x];
	}

	void Show()
	{
		for (int i = 0; i < data.size(); ++i)
		{
			cout << i + 1 << ". " << data[i] << endl;
		}
	}
};

class Command
{
protected:
	Document * doc;
public:
	virtual void Execute() = 0;
	virtual void unExecute() = 0;

	void setDocument(Document * _doc)
};


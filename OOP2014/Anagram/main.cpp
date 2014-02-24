#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Word
{
public:
	Word() :word(""), rank(0){}
	Word(string newWord, short newRank) :word(newWord), rank(newRank){}

	short getRank(){
		return rank;
	}

	string getword()
	{
		return word;
	}

private:
	
	short rank;
	string word;
};

class Dictionary
{
public:
	Dictionary(char* File_Name_Dict);

	string find(vector<short> key)
	{	
		map<vector<short>, Word>::iterator iter;
		iter = Dict.find(key);
		if (iter == Dict.end())
		{
			cout << "It's Error" << endl;
			return "ERROR";
		}
		Word mw = (*iter).second ;
		return mw.getword();
	}
	void ReadTxtFile();
private:
	map<vector<short>, Word> Dict;
	fstream Dict_File;
};


Dictionary::Dictionary(char* File_Name_Dict) 
{
	char* MyLine = "";
	Dict_File.open(File_Name_Dict, ios_base::in);

	ReadTxtFile();
}

void Dictionary::ReadTxtFile()
{
	string line;
	string word;
	
	vector<short> key = vector<short>(26);
		
	char* strRank = new char[3];
	short rank;

	
	while (!Dict_File.eof())
	{
		for (int it = 0; it < 26; it++)
		{
			key[it] = 0;
		}

		word.clear();
		line.clear();
		
		int i = 0;
		int j = 0;



		getline(Dict_File, line);


		while (!isspace(line[i]) && !ispunct(line[i]))
		{
			if (isupper(line[i]))
				line[i] = tolower(line[i]);
			word.push_back(line[i]);
			i++;
		}

		while (isspace(line[i]) || ispunct(line[i]))
		{
			i++;
		}

		while (!isspace(line[i]) && !ispunct(line[i]) && line[i] != '\0')
		{
			strRank[j] = line[i];
			i++;
			j++;
		}
		strRank[j] = '\0';

		rank = atoi((const char*)strRank);

		Word myWord(word, rank);

		for (int k = 0; k < word.length(); k++)
		{
			key[(short)(word[k] - 97)] ++;
		}

		if (Dict[key].getRank() < rank)
		Dict[key] = myWord;
	}

	delete strRank;
}



void main()
{
	Dictionary MyDict("Dictionary.txt");
	MyDict.ReadTxtFile();

	string AllString = "revo eey problme keew";
	vector<short> key = vector<short>(26);
	vector<string> sentence(0);
	string myword;

	for (int i = 0; i < AllString.length(); i++)
	{	
		for (int it = 0; it < 26; it++)
		{
			key[it] = 0;
		}

		if (!isspace(AllString[i]))
		{
			myword.push_back(AllString[i]);
			continue;
		}
			for (int k = 0; k < myword.length(); k++)
			{
				key[(short)(myword[k] - 97)] ++;
			}
			sentence.push_back(MyDict.find(key));
			myword.clear();
	}
	for (int k = 0; k < myword.length(); k++)
	{
		key[(short)(myword[k] - 97)] ++;
	}

	sentence.push_back(MyDict.find(key)); 


	cout << endl;
		
	vector<string>::iterator start = sentence.begin();
	vector<string>::iterator end = sentence.end();

	copy(start, end, ostream_iterator<string>(cout, " "));
	cout << endl;
	while (std::next_permutation(start, end))
	{
		

		copy(start, end, ostream_iterator<string>(cout, " "));
		/*for (vector<string>::iterator i = sentence.begin(); i < sentence.end(); i++)
		{
			cout << "  " << *i << "  ";
		}*/

		cout << endl;

	}

	
	copy(start, end, ostream_iterator<string>(cout, " "));

	
	cout << endl;






	/*for (int k = 0; k < word.length(); k++)
	{
		key[(short)(word[k] - 97)] ++;
	}*/

	//cout << MyDict.find(key) << endl;
	

	system("pause");
}
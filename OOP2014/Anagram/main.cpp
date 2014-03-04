#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#define NumberOfLetters		26
#define StringOfDigits		"1234567890"
#define EnglishAlphabet		"abcdefghijklmnopqrstuvwxyz"

class Word
{
public:
	Word() :word(""), rank(0){}
	Word(string newWord, short newRank) :word(newWord), rank(newRank){}
	short getRank(){return rank;}
	string getword(){return word;}
private:
	short rank;
	string word;
};

class Dictionary
{
public:
	Dictionary(char* File_Name_Dict);
	string find(vector<short> key);
	void ReadTxtFile();
private:
	map<vector<short>, Word> Dict;
	fstream Dict_File;
};

string Dictionary::find(vector<short> key)

{
	map<vector<short>, Word>::iterator iter;
	iter = Dict.find(key);
	if (iter == Dict.end())
	{
		cout << "It's Error" << endl;
		return "ERROR";
	}
	Word mw = (*iter).second;
	return mw.getword();
}

Dictionary::Dictionary(char* File_Name_Dict) 
{
	Dict_File.open(File_Name_Dict, ios_base::in);

	ReadTxtFile();
}

void Dictionary::ReadTxtFile()
{
	string line;
	string word;
	string rankstr;
	short rank;

	vector<short> key = vector<short>(NumberOfLetters);
	
	
	while (!Dict_File.eof())
	{
		for_each(key.begin(), key.end(), [](short &n){ n = 0; });
		word.clear();
		line.clear();
		getline(Dict_File, line);
		transform(line.begin(), line.end(), line.begin(), (int(*)(int))tolower);
		
		size_t count = 0;
		size_t it = line.find_first_of(',', count);
		word = line.substr(count, it - count);
		
		count = line.find_first_not_of(StringOfDigits, ++it);
		rankstr = line.substr(it, count);
		rank = atoi(rankstr.c_str());
		for_each(word.begin(), word.end(), [&key](char& c){key[(short)(c - 97)] ++;});
		
		Word myWord(word, rank);
		if (Dict[key].getRank() < rank)
			Dict[key] = myWord;
	}

}



void main()
{
	fstream input;
	Dictionary MyDict("Dictionary.txt");
	string allString;
	vector<short> key = vector<short>(NumberOfLetters);
	vector<string> sentence(0);
	string myword;
	size_t it = 0;
	size_t count = 0;

	input.open("input.txt", ios::in);
	getline(input,allString);
	transform(allString.begin(), allString.end(), allString.begin(), (int(*)(int))tolower);

	while (true){
		for_each(key.begin(), key.end(), [](short &n){ n = 0; });
		size_t it = allString.find_first_not_of(EnglishAlphabet, count);
		myword = allString.substr(count, it - count);
		
		for_each(myword.begin(), myword.end(), [&key](char& c){key[(short)(c - 97)] ++; });
		sentence.push_back(MyDict.find(key));
		count = it + 1;
		
		if (count == 0)
			break;
	}

	sort(sentence.begin(), sentence.end());
	for_each(sentence.begin(), sentence.end(), [](string it){cout << it << " "; });
	cout << endl;
	while (next_permutation(sentence.begin(), sentence.end()))
	{
		copy(sentence.begin(), sentence.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
	}
	cout << endl;
	
	system("pause");
}
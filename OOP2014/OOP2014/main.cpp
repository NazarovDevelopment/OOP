#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename Contain>
void write(Contain WordorSentence)
{
	Contain::iterator iter;

	for (iter = WordorSentence.begin(); iter < WordorSentence.end(); iter++)
	{
		cout << *iter << " ";
	}
}

template <typename Contain>
bool check(Contain WordorSentence)
{
	Contain::iterator BeginIterr = WordorSentence.begin();
	Contain::iterator EndIterr = WordorSentence.end()-- --;
	Contain::iterator CurrIterr = EndIterr;

	if (EndIterr == BeginIterr)
	{
		return 1;
	}

	for (Contain::iterator it = BeginIterr; it < EndIterr; it++)
	{	
		CurrIterr--;

		auto ob1 = *it;
		auto ob2 = *CurrIterr;

		if (ob1 != ob2)
		{
			return 0;
		}
		if (it >= CurrIterr){
			
			return 1;
		}
	}
}

template <typename Contain>
void IsPalindrome(Contain WordorSentence)
{
	write<Contain>(WordorSentence);
	cout << endl << " Reverse:" << endl;
	reverse(WordorSentence.begin(), WordorSentence.end());
	write<Contain>(WordorSentence);
	if (check<Contain>(WordorSentence))
	{	
		
		
		cout << endl << " it's Palindrome!!!" << endl << endl;
	}
	else{
		cout << endl << " it's  not Palindrome!!!" << endl << endl;
	}
}

void main()
{
	string AllLine = "aa oh oh aa oh oh aa";
	string Sentence;
	string word = "";
	vector<string> words;

	for (int i = 0; i < AllLine.length() + 1; i++){
		if (!isspace(AllLine[i]) && !ispunct(AllLine[i]) && AllLine[i]!='\0')
		{
			char c = AllLine[i];
			if (isupper(AllLine[i]))
				AllLine[i] = tolower(AllLine[i]);

			Sentence.push_back(AllLine[i]);
			word.push_back(AllLine[i]);
			
		}
		else
		{
			if (word != ""){
				words.push_back(word);
				IsPalindrome<string>(word);
				word.clear();
			}

			if (word == "")
				word.clear();
		}
	}
	




	cout << endl << endl;
	IsPalindrome<vector<string>>(words);
	
	cout << endl << endl;
	IsPalindrome<string>(Sentence);

	
	system("pause");
}
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename Contain, typename Intro>
void draw(Contain myContain)
{
	cout << endl << endl;
	
	for_each(myContain.begin(), myContain.end(), [](Intro it){cout << it << " "; });
	cout << endl;

	reverse(myContain.begin(),myContain.end());
	for_each(myContain.begin(), myContain.end(), [](Intro it){cout << it << " "; });
	cout << endl;

	if (IsPalindrome<Contain>(myContain))
		cout << "IT IS PALINDROME" << endl;
	else
		cout << "IT IS NOT PALINDROME" << endl;

	cout << endl;
}

template <typename Contain>
bool IsPalindrome(Contain WordOrSentence)
{
	Contain newContain = WordOrSentence;
	reverse(newContain.begin(), newContain.end());


	if (WordOrSentence == newContain)
		return true;
	else
		return false;
}

void main()
{
	fstream myfile;
	string allLine = "";
	string word = "";

	myfile.open("input.txt", ios::in);
	
	getline(myfile, allLine);
	string sentence;
	vector<string> words;

	transform(allLine.begin(), allLine.end(), allLine.begin(), (int(*)(int))tolower);
	
	size_t count = 0;

	while (true){
		size_t it = allLine.find_first_of(" ", count);
		word = allLine.substr(count, it - count);
		draw<string,char>(word);
		words.push_back(word);
		sentence = sentence + word;
		count = it + 1;
		if (count == 0)
			break;
	}

	draw<vector<string>, string>(words);
	draw<string,char>(sentence);
	system("pause");
}
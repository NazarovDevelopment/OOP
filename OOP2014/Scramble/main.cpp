#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

#define gnd 0
#define vcc 1
#define maximum_line_length 8

template <class T>
class Scrambler
{
public:
	Scrambler(const int onesNumber):number(onesNumber){}
	void ScrambleData(const T & data, T & outData) const
	{
		int counter = 0;
		for_each(data.begin(), data.end(), [this, &outData, &counter](int s)->void
		{
			outData.push_back(s);
			if (s == vcc) counter++;
			else counter = 0;

			if (counter == number)
			{
				counter = 0;
				outData.push_back(0);
			}
		});
	}
private:
	int number;
};

template <class T>
class Rescrambler
{
public:
	Rescrambler(const int onesNumber) :number(onesNumber){}
	void RescrambleData(const T & data, T & outData) const
	{
		int counter = 0;
		for_each(data.begin(), data.end(), [this, &outData, &counter](int s)->void
		{
			if (counter == number){ counter = 0; }
			else{
			if (s == vcc) counter++;
			else counter = 0;
			outData.push_back(s);
			}
		});
	}
private:
	int number;
};

void main()
{
	int valueSignal = gnd;
	vector<int> inputData;
	vector<int> outputData;

	cout << "Please enter data to transmit:" << endl;
	while (true)
	{
		valueSignal = 0;
		cin >> valueSignal;

		if (!cin.fail())
		{
			if (valueSignal == vcc || valueSignal == gnd)
				inputData.push_back(valueSignal);
			else{
				cout << "OK." << endl;
				break;
			}
		}
		else{
			cout << "OK." << endl;
			break;
		}
	}

	Scrambler<vector<int>> sc(3);
	Rescrambler<vector<int>> resc(3);

	int counter = 0;

	cout << endl;
	cout << "Scrambled data :" << endl;
	sc.ScrambleData(inputData, outputData);
	for_each(outputData.begin(), outputData.end(), [&counter](int it)->void{
		cout << it << " ";
		counter++;
		if (counter == maximum_line_length)
		{
			cout << endl;
			counter = 0;
		}
	});
	cout << endl;
	cout << "number of added bits:" << outputData.size() - inputData.size() << endl;
	
	cout << endl;
	cout << endl;
	cout << "Rescrambled data :" << endl;
	counter = 0;

	inputData.clear();
	resc.RescrambleData(outputData, inputData);
	for_each(inputData.begin(), inputData.end(), [&counter](int it)->void{
		cout << it << " ";
		counter++;
		if (counter == maximum_line_length)
		{
			cout << endl;
			counter = 0;
		}
	});

	cout << endl;
	system("pause");
}
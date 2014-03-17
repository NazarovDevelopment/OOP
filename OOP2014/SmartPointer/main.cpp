#include <iostream>
#include <cstdlib>

#include "SmartPointer.h"

using namespace std;

class foo{
public:
	static void call()
	{
		counter++;
	}
private:
	static int counter;
};

int foo::counter = 0;


void main()
{
	//int* i_ptr;
	

//	SmartPointer<int, foo> smart(i_ptr);
	

}
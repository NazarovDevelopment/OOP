#include <iostream>
#include <cstdlib>
#include "Complex.h"

#define _USE_MATH_DEFINES // for C++
#include <cmath>

using namespace std;



void main()
{
	Complex cmp;
	Complex cmp1(2, 6);
	double a = abs(cmp1);

	cmp = a;

	system("pause");
}

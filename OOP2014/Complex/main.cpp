#include <iostream>
#include <cstdlib>
#include "Complex.h"

#define _USE_MATH_DEFINES // for C++
#include <cmath>

using namespace std;



void main()
{
	Complex<double> cmp1(1,1);
	Complex<double> cmp2(1,1);
	
	Complex<double> cmp = cmp1.Pow(cmp2);
	//Complex<double> aaa = cmp1*cmp2;
	
	system("pause");
}

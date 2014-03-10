#include <iostream>
#include <cstdlib>
#include "Complex.h"

using namespace std;



void main()
{
	Complex<int> cmp1(5,0);
	Complex<int> cmp2(1, 1);
	Complex<int> cmp3 = cmp1 + cmp2;
	float i = cmp1.Module();
	


	system("pause");
}

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

const double exponena = 2.7182818284590452353602874713527;


template <typename T>
class Complex
{
public:

	//Constructs
	Complex() :real_part(0), complex_part(0){}
	Complex(T real, T comlex){ real_part = real; complex_part = comlex; }
	Complex(Complex<T>& cmp) :real_part(cmp.real_part), complex_part(cmp.complex_part){}

	//Operators
	void operator = (Complex<T> & right) {
		real_part = right.real_part;
		complex_part = right.complex_part;
	}

	Complex<T> operator + (const Complex<T>& right){
		return Complex<T>(real_part + right.real_part, complex_part + right.complex_part);
	}
	Complex<T> operator + (const T right){
		return Complex<T>(real_part + right, complex_part);
	}
	Complex<T> operator - (const Complex<T>& right){
		return Complex<T>(real_part - right.real_part, complex_part - right.complex_part);
	}
	Complex<T> operator - (const T right){
		return Complex<T>(real_part - right, complex_part);
	}
	Complex<T> operator * (const Complex<T>& right){
		return Complex<T>(real_part*right.real_part - complex_part*right.complex_part,
			real_part*right.complex_part + complex_part * right.real_part);
	}
	Complex<T> operator * (const T right){
		return Complex<T>(real_part*right,complex_part*right);
	}
	Complex<T> operator / (const T right){
		return Complex<T>((T) real_part/right,(T) complex_part/right);
	}
	Complex<T> operator / (const Complex<T>& right){
		return (*this)*right.MakeConjugate()/(right.real_part*right.real_part + right.complex_part*right.complex_part);
	}

	//bool
	bool operator == (const Complex<T>& right){
		return true ? ((real_part == right.real_part) && (complex_part == right.complex_part)) : false;
	}
	bool operator == (const T right){
	
		return true ? ((complex_part == 0) && (real_part == right)) : false;
	}
		

	//functions 
	Complex<double> Pow(const double right)
	{
		double mod = Module();
		double arg = Argument();
		return Complex<double>(pow(mod, right)*cos(right * arg), pow(mod, right)*sin(right * arg));
		
	}
	Complex<T> Pow(const Complex<T>& right)
	{
		double b = Argument();
		Complex<double> a(log(Module()), Argument());
		Complex<T> degree = a*right;
		return Complex<double>(pow(exponena, degree.RePart()) * cos(degree.ImPart()), pow(exponena, degree.RePart()) * sin(degree.ImPart()));
	}
	Complex<T> MakeConjugate(){
		return Complex<T>(real_part,-complex_part);
	}
	
	double Argument()
	{
		return acos(real_part / Module());
	}
	double Module(){
		return sqrt(real_part*real_part + complex_part*complex_part);
	}

	T RePart()
	{
		return real_part;
	}
	T ImPart()
	{
		return complex_part;
	}
	
private:
	T real_part;
	T complex_part;
};
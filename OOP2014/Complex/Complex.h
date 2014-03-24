#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

const double exponena = 2.7182818284590452353602874713527;

class Complex
{
public:

	//Constructors
	Complex() : real_part(0), complex_part(0){}
	Complex(const double &real, const double &comlex){ real_part = real; complex_part = comlex; }
	Complex(const Complex & cmp) :real_part(cmp.real_part), complex_part(cmp.complex_part){}

	//Operators
	Complex & operator = (const Complex & right);
	Complex & operator = (const double & right);
	
	Complex operator + (const Complex & right)const;
	Complex operator - (const Complex & right)const;
	Complex operator * (const Complex & right)const;
	Complex operator / (const Complex & right)const;
	Complex operator + (const double & right)const;
	Complex operator - (const double & right)const;
	Complex operator * (const double & right)const;
	Complex operator / (const double & right)const;
	
	
	Complex& operator += (const Complex & right);
	Complex& operator -= (const Complex & right);
	Complex& operator *= (const Complex & right);
	Complex& operator /= (const Complex & right);
	Complex& operator += (const double & right);
	Complex& operator -= (const double & right);
	Complex& operator *= (const double & right);
	Complex& operator /= (const double & right);
	//bool
	bool operator == (const Complex & right) const;
	bool operator == (const double & right) const;
		
	bool operator != (const Complex & right) const;
	bool operator != (const double & right) const;

	//functions 
	Complex Pow(const double & right) const;
	Complex Pow(const Complex & right) const;
	Complex MakeConjugate()const;
	
	double Argument()const;
	double RePart()  const;
	double ImPart()  const;	
	double Module()	 const;
	
	friend Complex& sqrt(double& right);
	friend Complex& cos(const Complex& right);
	friend Complex& sin(const Complex& right);

	friend std::ostream & operator <<(std::ostream & is, const Complex & right);
	friend std::istream & operator >>(std::istream & is, Complex & right);

	friend Complex Pow(const Complex& left, const Complex& right);
	friend Complex Pow(const double& left, const Complex& right);
	friend Complex Pow(const Complex& left, const double& right);
private:
	Complex& sqrt(const double & right)const;

	double real_part;
	double complex_part;
};

Complex operator + (const double & left, const Complex & right);
Complex operator - (const double & left, const Complex & right);
Complex operator * (const double & left, const Complex & right);
Complex operator / (const double & left, const Complex & right);
bool operator == (const double & left, const Complex & right);
bool operator != (const double & left, const Complex & right);

std::ostream & operator <<(std::ostream & is, const Complex & right);
std::istream & operator >>(std::istream & is, Complex & right);
double abs(const Complex&  cmp);
Complex& sqrt(const Complex&  cmp, const double& right);
Complex& sin(const Complex& right);
Complex& cos(const Complex& right);
double RePart(const Complex& right);
double ImPart(const Complex& right);

Complex Pow(const Complex& left, const Complex& right);
Complex Pow(const double& left, const Complex& right);
Complex Pow(const Complex& left, const double& right);


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
	Complex() :real_part(0), complex_part(0){}
	Complex(double real, double comlex){ real_part = real; complex_part = comlex; }
	Complex(Complex & cmp) :real_part(cmp.real_part), complex_part(cmp.complex_part){}

	//Operators
	Complex & operator = (const Complex & right){
		if (this == &right)
			return *this;

		real_part = right.real_part;
		complex_part = right.complex_part;
		return *this;
	}
	Complex & operator = (const double & right){
		if (this->real_part == right && this->complex_part)
			return *this;
		
		real_part = right;
		complex_part = 0;
		return *this;
	}
	
	Complex operator + (const Complex & right)const{
		return Complex(real_part + right.real_part, complex_part + right.complex_part);
	}
	Complex operator - (const Complex & right)const{
		return Complex(real_part - right.real_part, complex_part - right.complex_part);
	}
	Complex operator * (const Complex & right)const{
		return Complex(real_part*right.real_part - complex_part*right.complex_part,
			real_part*right.complex_part + complex_part * right.real_part);
	}
	Complex operator / (const Complex & right)const{
		return (*this)*right.MakeConjugate() / (right.real_part*right.real_part + right.complex_part*right.complex_part);
	}

	Complex operator + (const double & right)const{
		return Complex(real_part + right, complex_part);
	}
	Complex operator - (const double & right)const{
		return Complex(real_part - right, complex_part);
	}
	Complex operator * (const double & right)const{
		return Complex(real_part*right,complex_part*right);
	}
	Complex operator / (const double & right)const{
		return Complex((double)real_part / right, (double)complex_part / right);
	}
	
	
	Complex& operator += (const Complex & right){
		*this = *this + right;
		return *this;
	}
	Complex& operator -= (const Complex & right){
		*this = *this - right;
		return *this;
	}
	Complex& operator *= (const Complex & right){
		*this = *this * right;
		return *this;
	}
	Complex& operator /= (const Complex & right){
		*this = *this / right;
		return *this;
	}
	
	Complex& operator += (const double & right){
		real_part += right;
	}
	Complex& operator -= (const double & right){
		*this = *this - right;
		return *this;
	}
	Complex& operator *= (const double & right){
		*this = *this * right;
		return *this;
	}
	Complex& operator /= (const double & right){
		*this = *this / right;
		return *this;
	}

	//bool
	bool operator == (const Complex & right) const{
		return true ? ((real_part == right.real_part) && (complex_part == right.complex_part)) : false;
	}
	bool operator == (const double & right)   const{
	
		return true ? ((complex_part == 0) && (real_part == right)) : false;
	}
		
	bool operator != (const Complex & right) const
	{
		return !((*this) == right);
	}
	bool operator != (const double & right) const
	{
		return !((*this) == right);
	}

	friend std::ostream & operator <<(std::ostream & is, const Complex & right);
	friend std::istream & operator >>(std::istream & is, Complex & right);

	//functions 
	Complex Pow(const double & right) const
	{
		double mod = Module();
		double arg = Argument();
		return Complex(pow(mod, right)*cos(right * arg), pow(mod, right)*sin(right * arg));
		
	}
	Complex Pow(const Complex & right) const
	{
		double b = Argument();
		Complex a(log(Module()), Argument());
		Complex degree = a*right;
		return Complex(pow(exponena, degree.RePart()) * cos(degree.ImPart()), pow(exponena, degree.RePart()) * sin(degree.ImPart()));
	}
	Complex MakeConjugate()const{
		return Complex(real_part,-complex_part);
	}
	
	double Argument()const
	{
		return acos(real_part / Module());
	}
	double Module()	 const{
		return sqrt(real_part*real_part + complex_part*complex_part);
	}

	double RePart()  const
	{
		return real_part;
	}
	double ImPart()  const
	{
		return complex_part;
	}
	
private:
	double real_part;
	double complex_part;
};

Complex operator + (const double & left, const Complex & right){
	return right + left;
}
Complex operator - (const double & left, const Complex & right){
	return right * (-1) + left;
}
Complex operator * (const double & left, const Complex & right){
	return right * left;
}
Complex operator / (const double & left, const Complex & right){
	return right.MakeConjugate() *  left / pow(right.Module(),2);
}

bool operator == (const double & left, const Complex & right){
	return right == left;
}
bool operator != (const double & left, const Complex & right){
	return right != left;
}

std::ostream & operator <<(std::ostream & is, const Complex & right)
{
	if (right == 0){
		is << 0 << endl;
		return is;
	}

	if (right.real_part != 0)
		is << " " << right.real_part;// << endl;
	if (right.complex_part != 0){
		if (right.complex_part < 0)
			is << " - ";
		else 
			is << " + ";
		is << "i * " << abs(right.complex_part) << endl;
	}
	return is;
}
std::istream & operator >>(std::istream & is, Complex & right)
{
	regex re_cmp_exp("(\\s*(\\+|\\-)\\s*(i\\s*\\*\\s*)?(\\d+(?:\\.\\d+)?))+");
	regex re_cmp_num("^\\s*(\\+|\\-)\\s*(i\\s*\\*\\s*)?(\\d+(?:\\.\\d+)?)");
	string str;
	smatch match;

	getline(is, str);

	if (!regex_match(str, re_cmp_exp)) {
		str = "+" + str;
	}

	if (regex_match(str, re_cmp_exp)) {
		double tmp;
		while (regex_search(str, match, re_cmp_num)) {

			tmp = (match[1].str() == "+" ? +1 : -1)*stod(match[3].str());
			if (match[2].str() == "") {
				right += Complex(tmp, 0);
			}
			else {
				right += Complex(0, tmp);
			}
			str = match.suffix().str();
		}
	}

	return is;
}

double abs(const Complex&  cmp)
{
	return cmp.Module();
}
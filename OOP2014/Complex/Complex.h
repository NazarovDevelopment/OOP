#pragma once

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
	Complex<T> operator + (T right){
		return Complex<T>(real_part + right, complex_part);
	}
	Complex<T> operator - (const Complex<T>& right){
		return Complex<T>(real_part - right.real_part, complex_part - right.complex_part);
	}
	Complex<T> operator - (T right){
		return Complex<T>(real_part - right, complex_part);
	}
	Complex<T> operator * (const Complex<T>& right){
		return Complex<T>(real_part*right.real_part - complex_part*right.complex_part,
			real.part*right.complex_part - complex_part * right.real_part);
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

	Complex<T> operator ^ (const int right)
	{
		double mod = this->Module();
		double new_mod = mod;
		
		for (int i = 0; i < right; i++)
			new_mod = new_mod * mod;

		return Complex<T>((T)new_mod*cos(right * real_part / mod), (T)sin(complex_part / mod * right)*new_mod);
	}

	//bool
	bool operator == (const Complex<T>& right){
		return true ? ((real_part == right.real_part) && (complex_part == right.complex_part)) : false;
	}
	bool operator == (const T right){
	
		return true ? ((complex_part == 0) && (real_part == right)) : false;
	}
		

	//functions 
	Complex<T> MakeConjugate(){
		return Complex<T>(real_part,-complex_part);
	}
	double Module(){
		return sqrt(real_part*real_part + complex_part*complex_part);
	}
	
private:
	T real_part;
	T complex_part;
};
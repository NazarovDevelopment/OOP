//#include "Complex.h"
template<typename T>
void Complex<T>::operator = (Complex<T> & right){
	real_part = right.real_part;
	complex_part = right.complex_part;
}

template<typename T>
Complex<T> Complex<T>::operator+(const Complex<T>& right){
	return Complex<T>(real_part + right.real_part, complex_part + right.complex_part);
}
template<typename T>
Complex<T> Complex<T>::operator+(T right){
	return Complex<T>(real_part + right, complex_part);
}

template<typename T>
Complex<T> Complex<T>::operator-(const Complex<T>& right){
	return Complex<T>(real_part - right.real_part, complex_part - right.complex_part);
}

template<typename T>
Complex<T> Complex<T>::operator-(T right){
	return Complex<T>(real_part - right, complex_part);
}

template<typename T>
Complex<T> Complex<T>::operator * (const Complex& right){
	return Complex<T>(real_part*right.real_part - complex_part*right.complex_part,
		real.part*right.complex_part - complex_part * right.real_part);
}

template<typename T>
Complex<T> Complex<T>::operator * (const T right){
	return Complex<T>(real_part*right,complex_part*right);
}


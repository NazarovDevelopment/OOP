#include "Complex.h"


Complex & Complex::operator = (const Complex & right){
	if (this == &right)
		return *this;

	real_part = right.real_part;
	complex_part = right.complex_part;
	return *this;
}
Complex & Complex::operator = (const double & right){
	if (this->real_part == right && this->complex_part == 0)
		return *this;

	real_part = right;
	complex_part = 0;
	return *this;
}

Complex Complex::operator + (const Complex & right)const{
	return Complex(real_part + right.real_part, complex_part + right.complex_part);
}
Complex Complex::operator - (const Complex & right)const{
	return Complex(real_part - right.real_part, complex_part - right.complex_part);
}
Complex Complex::operator * (const Complex & right)const{
	return Complex(real_part*right.real_part - complex_part*right.complex_part,
		real_part*right.complex_part + complex_part * right.real_part);
}
Complex Complex::operator / (const Complex & right)const{
	return (*this)*right.MakeConjugate() / (right.real_part*right.real_part + right.complex_part*right.complex_part);
}

Complex Complex::operator + (const double & right)const{
	return Complex(real_part + right, complex_part);
}
Complex Complex::operator - (const double & right)const{
	return Complex(real_part - right, complex_part);
}
Complex Complex::operator * (const double & right)const{
	return Complex(real_part*right, complex_part*right);
}
Complex Complex::operator / (const double & right)const{
	return Complex((double)real_part / right, (double)complex_part / right);
}

Complex& Complex::operator += (const Complex & right){
	*this = *this + right;
	return *this;
}
Complex& Complex::operator -= (const Complex & right){
	*this = *this - right;
	return *this;
}
Complex& Complex::operator *= (const Complex & right){
	*this = *this * right;
	return *this;
}
Complex& Complex::operator /= (const Complex & right){
	*this = *this / right;
	return *this;
}

Complex& Complex::operator += (const double & right){
	real_part += right;
	return *this;
}
Complex& Complex::operator -= (const double & right){
	*this = *this - right;
	return *this;
}
Complex& Complex::operator *= (const double & right){
	*this = *this * right;
	return *this;
}
Complex& Complex::operator /= (const double & right){
	*this = *this / right;
	return *this;
}

//bool
bool Complex::operator == (const Complex & right) const{
	return (real_part == right.real_part) && (complex_part == right.complex_part);
}
bool Complex::operator == (const double & right)   const{

	return (complex_part == 0) && (real_part == right);
}

bool Complex::operator != (const Complex & right) const
{
	return !((*this) == right);
}
bool Complex::operator != (const double & right) const
{
	return !((*this) == right);
}

Complex Complex::MakeConjugate()const{
	return Complex(real_part, -complex_part);
}
double Complex::Argument()const
{
	return acos(real_part / Module());
}
double Complex::RePart()  const
{
	return real_part;
}
double Complex::ImPart()  const
{
	return complex_part;
}
double Complex::Module()	 const{
	return std::sqrt(real_part*real_part + complex_part*complex_part);
}

//-------------out-------------
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
	return right.MakeConjugate() *  left / pow(right.Module(), 2);
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

Complex& sqrt(const Complex&  cmp, const double& right)
{
	return Pow(cmp, 1 / right);
}
Complex& sin(const Complex& right)
{
	return Complex(std::sin(right.real_part)*cosh(right.complex_part), cos(right.real_part)*sinh(right.complex_part));
}
Complex& cos(const Complex& right)
{
	return sqrt(1 - Pow(right,2), 2);
}
double RePart(const Complex& right){
	return right.RePart();
}
double ImPart(const Complex& right){
	return right.ImPart();
}

Complex Pow(const Complex& left, const Complex& right)
{
	double b = left.Argument();
	Complex a(log(left.Module()), left.Argument());
	Complex degree = a*right;
	return Complex(pow(exponena, degree.RePart()) * cos(degree.ImPart()),
		pow(exponena, degree.RePart()) * std::sin(degree.ImPart()));
}
Complex Pow(const double& left, const Complex& right)
{
	Complex zero_complex(left,0);
	return Pow(zero_complex, right);
}
Complex Pow(const Complex& left, const double& right)
{
	double mod = left.Module();
	double arg = left.Argument();
	return Complex(pow(mod, right)*cos(right * arg), pow(mod, right)* std::sin(right * arg));
}

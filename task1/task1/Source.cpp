#include<iostream>
#include<cmath>
#include<ostream>

using namespace std;

class Complex
{
private:
	double re;
	double im;
	double sqrabs()
	{
		double sqrabs;
		sqrabs = (re * re) + (im * im);
		return sqrabs;
	}
public:
	Complex(double re = 0, double im = 0) :re(re),im(im) {}
	Complex(const Complex& complex) :re(complex.re), im(complex.im) {}
	~Complex() {}
	Complex& operator=(Complex& complex)
	{
		re = complex.re;
		im = complex.im;
		return *this;
	}
	double abs()
	{
		double abs;
		abs = sqrt(((re) * (re)) + ((im) * (im)));
		return abs;
	}
	double arg()
	{
		double arg;
		arg = atan(re / im);
		return arg;
	}
	Complex reverse()
	{
		re = re / sqrabs();
		im = im / sqrabs();
		return(re, im);
	}
	friend Complex operator*(Complex complex1, Complex complex2)
	{
		return Complex(complex1.re * complex2.re - complex1.im * complex2.re);
	}
	friend Complex operator*(double d, Complex complex)
	{
		return Complex(d * complex.re, d * complex.im);
	}
	friend Complex operator*(Complex complex, double d)
	{
		return Complex(complex.re * d, complex.im * d);
	}
	friend Complex operator+(Complex complex1, Complex complex2)
	{
		return Complex(complex1.re + complex2.re, complex1.im + complex2.im);
	}
	friend Complex operator/(Complex complex1, Complex complex2)
	{
		Complex temp;
		double r = (complex2.re * complex2.re) + (complex2.im * complex2.im);
		temp.re = ((complex1.re * complex2.re) + (complex1.im * complex2.im)) / r;
		temp.re = ((complex1.im * complex2.re) - (complex1.re * complex2.im)) / r;
		return temp;
	}
	friend ostream& operator<<(ostream& stream, const Complex& complex)
	{

	}

};
#include "Complex.h"
#include <iostream>
#include <cmath>

double Complex::modulus() const { return sqrt(real * real + imag * imag); }
bool Complex::operator==(const Complex& other) const { return real == other.real && imag == other.imag; }
bool Complex::operator!=(const Complex& other) const { return real != other.real || imag != other.imag; }
bool Complex::operator<(const Complex& other) const
{
	if (modulus() == other.modulus())
		return real < other.real;
	else
		return modulus() < other.modulus();
}
bool Complex::operator>(const Complex& other) const
{
	if (modulus() == other.modulus())
		return real > other.real;
	else
		return modulus() > other.modulus(); 
}
void Complex::show() const { std::cout << real << ',' << imag << std::endl; }
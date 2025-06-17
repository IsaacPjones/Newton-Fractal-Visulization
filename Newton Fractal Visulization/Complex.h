#pragma once
#include<iostream>
#include<cmath>

using namespace std;

class Complex
{
private:
	double imag;
	double real;
public:
	class InputOutOfBoundsExeception {
	private:
		const char* errorMessage;
		const char* offendingIndex;
	public:
		InputOutOfBoundsExeception(const char*, const char*);
		const char* returnError();
		const char* returnOffendingIndex();
	};
	~Complex();
	Complex();
	Complex(const Complex&);
	Complex(double);
	Complex(double, double);
	double& operator[](const char*);
	friend const Complex operator*(const Complex&, const Complex&);
	friend const Complex operator/(const Complex&, const Complex&);
	friend const Complex operator+(const Complex&, const Complex&);
	friend const Complex operator-(const Complex&, const Complex&);
	friend double getMagnitude(const Complex&);
};

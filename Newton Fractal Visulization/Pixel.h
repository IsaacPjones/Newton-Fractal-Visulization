#pragma once
#include<iostream>
#include<fstream>

using namespace std;
using std::ofstream;

class Pixel

{
private:
	unsigned int red;
	unsigned int green;
	unsigned int blue;
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
	~Pixel();
	const unsigned int& operator[](const char*) const;
	Pixel();
	Pixel(const Pixel&);
	Pixel(unsigned int, unsigned int, unsigned int);
	friend ofstream& operator<<(ofstream&, const Pixel&);
};

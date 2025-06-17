#pragma once
#include "Complex.h"
#include "Pixel.h"
#include <cstdlib> 
#include <algorithm>
#include <fstream>

using namespace std;

class Fractal
{
private:
	unsigned int cols;
	unsigned int rows;
	static const unsigned int maxIter = 30;
	Pixel** grid;

	Pixel determinePixelColor(Complex);
	void makeNewtonFractal();

public:
	~Fractal();
	Fractal();
	Fractal(const Fractal&);
	Fractal(Fractal&&);
	Fractal(unsigned int, unsigned int);
	const Fractal& operator=(const Fractal&);
	Fractal& operator=(Fractal&&);

	void allocateGrid();
	void deallocateGrid();

	friend void saveToPPM(Fractal&, const char*);
}; 

#include "Complex.h"
#include "Pixel.h"
#include "Fractal.h"




Fractal::~Fractal()
{
	for (unsigned int i = 0; i < rows; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}

Fractal::Fractal() : rows(0), cols(0) {
	cout << "Fractal class default constructor" << endl;
	allocateGrid();
}

Fractal::Fractal(const Fractal& a) : rows(a.rows), cols(a.cols)
{
	cout << "Fractal class copy constructor" << endl;
	allocateGrid();
}

Fractal::Fractal(Fractal&& f)
{
	this->cols = f.cols;
	this->rows = f.rows;
	this->grid = f.grid;

	f.grid = nullptr;
	f.rows = 0;
	f.cols = 0;

}

Fractal::Fractal(unsigned int x, unsigned int y) : cols(x), rows(y)
{
	cout << "Fractal class two-arg constructor" << endl;
	allocateGrid();
}

const Fractal& Fractal::operator=(const Fractal& f)
{
	if (this != &f)
	{
		this->cols = f.cols;
		this->rows = f.rows;
		allocateGrid();
	}
	return *this;
}


Fractal& Fractal::operator=(Fractal&& f)
{
	if (this != &f)
	{
		this->cols = f.cols;
		this->rows = f.rows;
		this->grid = f.grid;

		f.grid = nullptr;
		f.rows = 0;
		f.cols = 0;
	}
	return *this;
}


void Fractal::allocateGrid()
{
	if (rows == 0 && cols == 0)
		grid = nullptr;
	grid = new Pixel * [rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
	}
	makeNewtonFractal();

}



void Fractal::deallocateGrid()
{
	for (unsigned int i = 0; i < rows; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
	grid = nullptr;
}





void Fractal::makeNewtonFractal()
{
	Complex Z;
	double step_height = 4.0 / rows;
	double step_width = 4.0 / cols;
	for (unsigned int j = 0; j < rows; j++)
	{
		for (unsigned int k = 0; k < cols; k++)
		{
			Z["imaginary"] = 2.0 - (j * step_height);
			Z["real"] = (k * step_width) - 2.0;
			grid[j][k] = determinePixelColor(Z);
		}

	}

}


Pixel Fractal::determinePixelColor(Complex Z)
{
	const double tol = 1E-4;
	double diff = 1.0;
	const double test = 0.58974;
	unsigned int iter = 0;
	unsigned int color = 0;
	Complex Znew;
	while (iter < 512)
	{
		iter++;
		Znew = Z - ((Z * Z * Z) - (2.0 * Z) + 2.0) / ((3.0 * Z * Z) - 2.0);
		diff = getMagnitude(Z - Znew);
		Z = Znew;
		if (diff < tol)
		{
			color = maxIter - min(iter, maxIter);
			if (abs(Z["imaginary"]) < tol)
				return Pixel{ color, color, 0 };

			else if (abs(Z["imaginary"] - test) < tol)
				return Pixel{ 0, color, color };

			else if (abs(Z["imaginary"] + test) < tol)
				return Pixel{ color, 0, color };

		}
	}
	return Pixel{ 0, 0, 0 };
}



void saveToPPM(Fractal& f, const char* name)
{
	cout << "making image" << endl;
	ofstream image;
	image.open(name);
	if (image.is_open())
	{
		image << "P3\n" << "# Fractal" << "\n" << f.cols << " " << f.rows << "\n" << f.maxIter << endl; // sets header for PPM file
	}
	else
	{
		cout << "Error opening file" << endl;
	}
	for (unsigned int row = 0; row < f.rows; row++)
	{
		for (unsigned int col = 0; col < f.cols; col++)
		{
			image << f.grid[row][col] << " ";
		}
		image << endl;
	}
	image.close();

}

#include "Pixel.h"

Pixel::~Pixel() {

}
const unsigned int& Pixel::operator[](const char* input) const {
	if (input == "red")
		return this->red;
	else if (input == "green")
		return this->green;
	else if (input == "blue")
		return this->blue;
	else
		throw InputOutOfBoundsExeception(">Pixel class:Error input is not red, green or blue,line 13", input);
}
ofstream& operator<<(ofstream& out, const Pixel& p1) {
	out << p1["red"] << " " << p1["green"] << " " << p1["blue"];
	return out;
}
Pixel::Pixel() :red(0), green(0), blue(0)
{
}
Pixel::Pixel(const Pixel& p1) :red(p1.red), green(p1.green), blue(p1.blue)
{
}
Pixel::Pixel(unsigned int red, unsigned int green, unsigned int blue)
	:red(red), green(green), blue(blue)
{
}
Pixel::InputOutOfBoundsExeception::InputOutOfBoundsExeception(const char* message, const char* index)
	:errorMessage(message), offendingIndex(index)
{

}
const char* Pixel::InputOutOfBoundsExeception::returnError() {
	return errorMessage;
}
const char* Pixel::InputOutOfBoundsExeception::returnOffendingIndex() {
	return offendingIndex;
}
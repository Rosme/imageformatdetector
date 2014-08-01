#include "detector.hpp"
#include "format.hpp"

#include <iostream>

void JPGDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for JPG\n";
}

void PNGDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for PNG\n";
}

void BMPDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for BMP\n";
}

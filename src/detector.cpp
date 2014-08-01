#include "detector.hpp"
#include "format.hpp"

#include <iostream>

void JPGDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing JPG Detector\n";
}

void PNGDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing PNG Detector\n";
}

void BMPDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing BMP Detector\n";
}

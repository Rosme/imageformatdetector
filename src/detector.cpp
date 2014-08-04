#include "detector.hpp"
#include "format.hpp"
#include "image.hpp"

#include <iostream>

void JPGDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for JPG\n";

	if (!format) {
		std::cout << "Not JPG\n";
	}
}

void PNGDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for PNG\n";

	//PNG is define by an 8 byte signature
	// 89 50 4E 47 0D 0A 1A 0A
	// See http://en.wikipedia.org/wiki/Portable_Network_Graphics#Technical_details
	std::string signature = image.substr(0, 8);
	if (signature == "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a") {
		std::cout << "PNG 8-Byte Signature is valid. Image file is PNG.\n";
		format = Image::Formats["png"];
	}

	if (!format) {
		std::cout << "Not PNG\n";
	}
}

void BMPDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for BMP\n";

	if (!format) {
		std::cout << "Not BMP\n";
	}
}

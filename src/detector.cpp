#include "detector.hpp"
#include "format.hpp"
#include "image.hpp"

#include <iostream>

void JPGDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for JPG\n";

	//JPG is define by a very specific structure.
	//A JPG file starts with a 12 bytes signature
	// FF D8 FF E0 00 10 4A 46 49 46 00 01
	//See http://en.wikipedia.org/wiki/JPEG#Syntax_and_structure
	std::string signature = image.substr(0, 4);
	const std::string jpgSignature = "\xff\xd8\xff\xe0";
	//TODO: Make jpgSignature = \xff\xd8\xff\xe0\x00\x10\x4a\x46\x49\x46\x00\x01 work
	if (signature == jpgSignature) {
		std::cout << "JPG Signature found. Image file is JPG\n";
		format = Image::Formats["jpeg"];
	}

	if (!format) {
		std::cout << "Not JPG\n";
	}
}

void PNGDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for PNG\n";

	//PNG is define by an 8 byte signature
	// 89 50 4E 47 0D 0A 1A 0A
	//See http://en.wikipedia.org/wiki/Portable_Network_Graphics#Technical_details
	std::string signature = image.substr(0, 8);
	const std::string pngSignature = "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a";
	if (signature == pngSignature) {
		std::cout << "PNG Signature found. Image file is PNG.\n";
		format = Image::Formats["png"];
	}

	if (!format) {
		std::cout << "Not PNG\n";
	}
}

void BMPDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for BMP\n";

	//BMP is define by a 14 Byte header
	//The signature is a 2 byte value starting at the start of the file
	// Default signature:
	// 42 4D   (BM)
	// Can be:
	// 42 41   (BA)
	// 43 49   (CI)
	// 43 50   (CP)
	// 49 43   (IC)
	// 50 54   (PT)
	//The 12 other bytes are useless to identifying the formats.
	//See http://en.wikipedia.org/wiki/BMP_file_format#File_structure
	std::vector<std::string> bmpSignatures;
	bmpSignatures.push_back("\x42\x4d");
	bmpSignatures.push_back("\x42\x41");
	bmpSignatures.push_back("\x43\x49");
	bmpSignatures.push_back("\x43\x50");
	bmpSignatures.push_back("\x49\x43");
	bmpSignatures.push_back("\x50\x54");

	std::string signature = image.substr(0, 2);
	const auto it = std::find(std::begin(bmpSignatures), std::end(bmpSignatures), signature);
	if (it != std::end(bmpSignatures)) {
		std::cout << "BMP Signature Found: " << *it << ". Image file is BMP.\n";
		format = Image::Formats["bmp"];
	}

	if (!format) {
		std::cout << "Not BMP\n";
	}
}

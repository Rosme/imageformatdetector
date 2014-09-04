#include "detector.hpp"
#include "format.hpp"
#include "image.hpp"

#include <iostream>
#include <algorithm>

void JPGDetector::detect(const std::string& image, Format& format) {
	std::cout << "Testing for JPEG\n";
	//Default JPEG image
	//The default JPG image has a 2bytes header signature and a 2bytes ending signature
	// Header Signature: FF D8
	// Ending Signature: FF D9
	//See http://en.wikipedia.org/wiki/JPEG#Syntax_and_structure
	const std::string jpgHeaderSignature = "\xff\xd8";
	const std::string jpgEndingSignature = "\xff\xd9";
	std::string headerSignature = image.substr(0, 2);
	std::string endingSignature = image.substr(image.size() - 2, 2); //Getting the last two bytes
	if (headerSignature == jpgHeaderSignature && endingSignature == jpgEndingSignature) {
		std::cout << "JPG Signature Found. Image file is JPEG.\n";
		format = Image::Formats["jpeg"];
		return;
	}

	std::cout << "Testing for JPEG/JFIF\n";
	//If not a classic JPEG image, we'll test something else
	//A JPEG/JFIF has a 5 bytes signature that represents JFIF with a null terminated string
	// 4A 46 49 46 00
	// The signature is located at the 7 byte
	const std::string jfifSignature = "\x4a\x46\x49\x46";
	headerSignature = image.substr(6, 4);
	if (headerSignature == jfifSignature) {
		std::cout << "JFIF Signature Found. Image is JPEG/JFIF.\n";
		format = Image::Formats["jfif"];
		return;
	}

	std::cout << "Testing short JPEG signature\n";
	//We'll test only the short signature of a jpeg, which is the 2 first bytes.
	//It's not guarantee it's a JPEG, but chances are high it is.
	headerSignature = image.substr(0, 2);
	if (headerSignature == jpgHeaderSignature) {
		std::cout << "HEADER JPG Signature Found. High chance of this being a JPG image.\n";
		format = Image::Formats["jpg"];
		return;
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

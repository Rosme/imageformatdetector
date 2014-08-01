#include "image.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const Format& format) {
	return out << "Extension: " + format.extension + " - " + format.name + '\n';
}

int main(int argc, char* argv[]) {

	Image img("test.jpg");
	img.load();

	std::cout << "File Type Detector\n";
	std::cout << "File loaded: " + img.filename() + '\n';
	std::cout << "Format Based Name: \n";
	std::cout << img.nameBasedFormat();
	std::cout << "Expected Format: \n";
	std::cout << img.expectedFormat();
	std::cout << "Detecting Real Type: \n";
	img.detectFormat();
	std::cout << "Real Format: \n";
	std::cout << img.realFormat();

	std::cin.get();
	return 0;
}

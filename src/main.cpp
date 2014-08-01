#include "image.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const Format& format) {
	return out << "Extension: " + format.extension + " - " + format.name + '\n';
}

bool operator==(const Format& lhs, const Format& rhs) {
	return lhs.extension == rhs.extension && lhs.format == rhs.format && lhs.name == rhs.name;
}

int main(int argc, char* argv[]) {
	//Loading format
	Image::loadFormats();
	if (argc == 1) {
		std::cout << "No file given";
		std::cin.get();
		return 0;
	}
	std::string filepath = argv[1];
	for (auto& c : filepath) {
		if (c == '\\')
			c = '/';
	}
	Image img(filepath);
	img.load();

	std::cout << "File Type Detector\n";
	std::cout << "File loaded: " + img.filename() + "\n\n";
	std::cout << "Format Based Name: \n";
	std::cout << img.nameBasedFormat();
	std::cout << "\nExpected Format: \n";
	std::cout << img.expectedFormat();
	std::cout << "\nDetecting Real Type\n";
	img.detectFormat();
	std::cout << "Real Format: \n";
	std::cout << img.realFormat();

	std::cin.get();
	return 0;
}

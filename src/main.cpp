#include "image.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const Format& format) {
	return out << "Extension: " + format.extension + " - " + format.name + '\n';
}

bool operator==(const Format& lhs, const Format& rhs) {
	return lhs.extension == rhs.extension && lhs.format == rhs.format && lhs.name == rhs.name;
}

bool operator!=(const Format& lhs, const Format& rhs) {
	return !(lhs == rhs);
}

int main(int argc, char* argv[]) {
	//Loading format
	Image::loadFormats();
	if (argc == 1) {
		std::cout << "No file given";
		std::cin.get();
		return 0;
	}
	std::string arg = argv[1];
	std::string filepath;
	if(arg == "-i") {
		std::cout << "Interactive Mode\n";
		std::cout << "Indicates path to file: ";
		std::getline(std::cin, filepath);
	} else {
		filepath = argv[1];
	}
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
	std::cout << "\nDetecting Real Type...\n\n";
	img.detectFormat();
	std::cout << "\nReal Format: \n";
	std::cout << img.realFormat();
#ifdef _MSC_VER
	std::cin.get();
#endif
	return 0;
}

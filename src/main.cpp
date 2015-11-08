/*
* Copyright (c) 2015 Jean-Sébastien Fauteux
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from
* the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it freely,
* subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not claim
*    that you wrote the original software. If you use this software in a product,
*    an acknowledgment in the product documentation would be appreciated but is
*    not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

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
		std::cout << "No file given\n";
#ifdef _MSC_VER
        std::cin.get();
#endif
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

	std::cout << "File Format Detector\n";
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

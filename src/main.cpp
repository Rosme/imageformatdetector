#include "image.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

	Image img("test.jpg");

	std::cout << img.expectedFormat().extension;


	std::cin.get();
	return 0;
}


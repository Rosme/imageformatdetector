#pragma once

#include <string>
#include <ostream>

enum ImageFormat {
	JPG,
	PNG,
	BMP
};

struct Format {
	Format(){}
	Format(const std::string& ext, const std::string& n)
		: extension(ext), name(n) {
	}

	std::string extension;
	std::string name;
};

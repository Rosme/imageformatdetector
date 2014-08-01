#pragma once

#include <string>
#include <ostream>

struct Format {
	Format(){}
	Format(const std::string& ext, const std::string& n)
		: extension(ext), name(n) {
	}

	std::string extension;
	std::string name;
};

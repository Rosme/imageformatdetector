#pragma once

#include <string>

enum ImageFormat {
	JPG,
	PNG,
	BMP,
	Unknown
};

struct Format {
	Format()
		: Format("**", "Unknown Format", ImageFormat::Unknown) {}
	Format(const std::string& ext, const std::string& n, const ImageFormat f)
		: extension(ext), name(n), format(f) {
	}

	std::string extension;
	std::string name;
	ImageFormat format;

	operator bool() const {
		return format != ImageFormat::Unknown;
	}
};

bool operator==(const Format& lhs, const Format& rhs);
bool operator!=(const Format& lhs, const Format& rhs);

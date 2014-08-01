#pragma once

#include <string>
#include <map>

#include "format.hpp"

class Image {
public:
	static std::map<std::string, Format> Formats;
	static void loadFormats();

public:
	Image();
	explicit Image(const std::string& file);
	
	void load(const std::string& file = "");
	const Format& expectedFormat() const;
	const Format& realFormat() const;
	void setRealFormat(const Format& format);

private:
	std::string mFile;
	const Format UnknownFormat;
	Format mRealFormat;
	Format mExpectedFormat;
	std::string mContent;
};
#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "format.hpp"

class Detector;
typedef std::unique_ptr<Detector> DetectorPtr;

class Image {
public:
	static std::unordered_map<std::string, Format> Formats;
	static void loadFormats();

public:
	Image();
	explicit Image(const std::string& file);
	
	void load(const std::string& file = "");
	const Format& expectedFormat() const;
	const Format& realFormat() const;
	const Format& nameBasedFormat() const;
	void detectFormat();
	const std::string& filename() const;

private:
	std::string mFile;
	const Format UnknownFormat;
	Format mRealFormat;
	Format mExpectedFormat;
	Format mNameBasedFormat;
	std::string mContent;
	DetectorPtr mDetector;
};

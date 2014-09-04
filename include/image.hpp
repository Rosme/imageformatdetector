#pragma once

#include <string>
#include <memory>
#include <functional>
#include <vector>
#ifdef _MSC_VER
#include <unordered_map>
#else
#include <map>
#endif

#include "format.hpp"
#include "detector.hpp"

typedef std::unique_ptr<Detector> DetectorPtr;

class Image {
public:
	static
#ifdef _MSC_VER	
	std::unordered_map<std::string, Format>
#else	
	std::map<std::string, Format>
#endif	
	Formats;
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

	template<class T>
	void registerFormat(ImageFormat format);

private:
	std::string mFile;
	Format mRealFormat;
	Format mExpectedFormat;
	Format mNameBasedFormat;
	std::string mContent;
	DetectorPtr mDetector;

#ifdef _MSC_VER
	std::unordered_map<ImageFormat, std::function<DetectorPtr()>> 
#else
	std::map<ImageFormat, std::function<DetectorPtr()>>
#endif
	mDetectors;
};

template<class T>
void Image::registerFormat(ImageFormat format) {
	mDetectors[format] = [this]() {
		return DetectorPtr(new T);
	};
}

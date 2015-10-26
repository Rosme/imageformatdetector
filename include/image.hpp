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

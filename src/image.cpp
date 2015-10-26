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

#include <algorithm>
#include <fstream>
#include <cassert>

#include <iostream>

#ifdef _MSC_VER
	std::unordered_map<std::string, Format> Image::Formats;
#else
	std::map<std::string, Format> Image::Formats;
#endif


void Image::loadFormats() {
	//Listing the extensions for the different iamge formats
	//PNG
	Formats["png"] = Format("png", "PNG - Portable Network Graphics", ImageFormat::PNG);
	//BMP
	Formats["bmp"] = Format("bmp", "BMP - Bitmap", ImageFormat::BMP);
	//JPG - JPEG
	Formats["jpg"] = Format("jpg", "JPEG - Joint Photographic Experts Group", ImageFormat::JPG);
	Formats["jpeg"] = Format("jpeg", "JPEG - Joint Photographic Experts Group", ImageFormat::JPG);
	Formats["jpe"] = Format("jpe", "JPEG - Joint Photographic Experts Group", ImageFormat::JPG);
	Formats["jif"] = Format("jif", "JPEG - JPEG File Interchange Format", ImageFormat::JPG);
	Formats["jfif"] = Format("jfif", "JPEG - JPEG File Interchange Format", ImageFormat::JPG);
	Formats["jfi"] = Format("jfi", "JPEG - JPEG File Interchange Format", ImageFormat::JPG);
	//GIF
	Formats["gif"] = Format("gif", "GIF - Graphics Interchange Format", ImageFormat::GIF);
}

Image::Image()
	:
#if _MSC_VER == 1700
	mFile(""), mDetector(nullptr)
#else
	Image("")
#endif
	{}

Image::Image(const std::string& file)
	: mFile(file), mDetector(nullptr) {
	//Registering the different type of format to their detector
	registerFormat<JPGDetector>(ImageFormat::JPG);
	registerFormat<PNGDetector>(ImageFormat::PNG);
	registerFormat<BMPDetector>(ImageFormat::BMP);
	registerFormat<GIFDetector>(ImageFormat::GIF);

	//Trying to find format based on extension
	std::string fileExtension = mFile.substr(mFile.rfind('.')+1);
	mNameBasedFormat.extension = fileExtension;
	auto it = Formats.find(fileExtension);
	if (it != Formats.end())
		mExpectedFormat = it->second;
}

void Image::load(const std::string& file) {
	//Reading the file and loading into memory
	std::ifstream ifs(mFile, std::ios::binary);
	assert(ifs.is_open());

	ifs.seekg(0, ifs.end);
	unsigned int length = ifs.tellg(); //Finding size of file
	ifs.seekg(0, ifs.beg);

	mContent.resize(length, ' '); //Reserving the space for the file
	char* begin = &*mContent.begin();

	ifs.read(begin, length);
	ifs.close();
}

const Format& Image::expectedFormat() const {
	return mExpectedFormat;
}

const Format& Image::realFormat() const {
	return mRealFormat;
}

const Format& Image::nameBasedFormat() const {
	return mNameBasedFormat;
}

void Image::detectFormat() {
	//First let's see if the extension is valid
	ImageFormat imgFormat = Formats[mExpectedFormat.extension].format;
	mDetector = mDetectors[imgFormat]();
	assert(mDetector != nullptr);
	mDetector->detect(mContent, mRealFormat);

	//Verifying if we found the format
	//If so, it means the extension was true
	if (mRealFormat) {
		return;
	}

	//Second, if we did not find the format
	//Let's do more test
	//We'll store all the tested format to make sure we don't test them twice
	std::vector<ImageFormat> testedFormats;
	testedFormats.push_back(imgFormat); //Will be the extension format

	for (auto& it : mDetectors) {
		if (std::find(std::begin(testedFormats), std::end(testedFormats), it.first) != std::end(testedFormats)) {
			//Did we find the format in the already tested? If yes, let's skip it
			continue;
		}

		//We'll take the next detector and try it
		mDetector = it.second();
		assert(mDetector != nullptr);
		mDetector->detect(mContent, mRealFormat);
		//Verifying if we found a format
		if (mRealFormat)
			return;
		testedFormats.push_back(it.first); //Storing the tested format to make sure we won't retest it
	}
}

const std::string& Image::filename() const {
	return mFile;
}

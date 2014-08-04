#include "image.hpp"

#include <algorithm>
#include <fstream>
#include <cassert>

#include <iostream>

std::unordered_map<std::string, Format> Image::Formats;

void Image::loadFormats() {
	//Listing the extensions for the different iamge formats
	//PNG
	Formats["png"] = Format("png", "PNG - Portable Network Graphics", ImageFormat::PNG);
	//BMP
	Formats["bmp"] = Format("bmp", "BMP - Bitmap", ImageFormat::BMP);
	//JPG - JPEG
	Formats["jpg"] = Format("jpg", "JPEG - Joint Photographic Experts Group", ImageFormat::JPG);
	Formats["jpeg"] = Format("jpeg", "JPEG - Joint Photographic Experts Group", ImageFormat::JPG);
	Formats["jpe"] = Format("jpeg", "JPEG - Joint Photographic Experts Group", ImageFormat::JPG);
	Formats["jif"] = Format("jpeg", "JPEG - Joint Photographic Experts Group", ImageFormat::JPG);
	Formats["jfif"] = Format("jpeg", "JPEG - Joint Photographic Experts Group", ImageFormat::JPG);
	Formats["jfi"] = Format("jpeg", "JPEG - Joint Photographic Experts Group", ImageFormat::JPG);
}

Image::Image()
	: Image("") {}

Image::Image(const std::string& file)
	: mFile(file), mDetector(nullptr) {
	//Registering the different type of format to their detector
	registerFormat<JPGDetector>(ImageFormat::JPG);
	registerFormat<PNGDetector>(ImageFormat::PNG);
	registerFormat<BMPDetector>(ImageFormat::BMP);

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
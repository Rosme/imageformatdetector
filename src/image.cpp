#include "image.hpp"

#include <algorithm>
#include <fstream>
#include <cassert>

std::unordered_map<std::string, Format> Image::Formats;

void Image::loadFormats() {
	Formats["png"] = Format("png", "PNG - Portable Network Graphics");
	Formats["bmp"] = Format("bmp", "BMP - Bitmap");
	Formats["jpg"] = Format("jpg", "JPEG - Joint Photographic Experts Group");
	Formats["jpeg"] = Format("jpeg", "JPEG - Joint Photographic Experts Group");
}

Image::Image()
	: Image("") {}

Image::Image(const std::string& file)
	: mFile(file), UnknownFormat("**", "Unknown Format") {
	std::string fileExtension = mFile.substr(mFile.rfind('.')+1);
	mNameBasedFormat.extension = fileExtension;
	auto it = Formats.find(fileExtension);
	mExpectedFormat = UnknownFormat;
	if (it != Formats.end())
		mExpectedFormat = it->second;
}

void Image::load(const std::string& file) {
	std::ifstream ifs(mFile, std::ios::binary);
	assert(ifs.is_open());

	ifs.seekg(0, ifs.end);
	std::fstream::pos_type length = ifs.tellg();
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

}

const std::string& Image::filename() const {
	return mFile;
}

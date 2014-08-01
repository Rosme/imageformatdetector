#include "image.hpp"

#include <algorithm>

std::map<std::string, Format> Image::Formats;

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
	mExpectedFormat.extension = fileExtension;
}

void Image::load(const std::string& file) {

}

const Format& Image::expectedFormat() const {
	return mExpectedFormat;
}

const Format& Image::realFormat() const {
	return mRealFormat;
}

void Image::setRealFormat(const Format& format) {

}
#pragma once

#include <string>

class Format;

struct Detector {
	virtual void detect(const std::string& image, Format& format) = 0;
};

class JPGDetector {
	void detect(const std::string& image, Format& format);
};

class PNGDetector {
	void detect(const std::string& image, Format& format);
};

class BMPDetector {
	void detect(const std::string& image, Format& format);
};

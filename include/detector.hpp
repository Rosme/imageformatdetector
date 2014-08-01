#pragma once

#include <string>

struct Format;

struct Detector {
	virtual void detect(const std::string& image, Format& format) = 0;
};

class JPGDetector : public Detector {
	void detect(const std::string& image, Format& format);
};

class PNGDetector : public Detector {
	void detect(const std::string& image, Format& format);
};

class BMPDetector : public Detector {
	void detect(const std::string& image, Format& format);
};

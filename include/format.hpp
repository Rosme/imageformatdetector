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

enum ImageFormat {
	JPG,
	PNG,
	BMP,
	GIF,
	Unknown
};

struct Format {
	Format()
		:
#if _MSC_VER == 1700
		extension("**"), name("Unknown Format"), format(ImageFormat::Unknown)
#else
	Format("**", "Unknown Format", ImageFormat::Unknown)
#endif
	{}
	Format(const std::string& ext, const std::string& n, const ImageFormat f)
		: extension(ext), name(n), format(f) {
	}

	std::string extension;
	std::string name;
	ImageFormat format;

	operator bool() const {
		return format != ImageFormat::Unknown;
	}
};

bool operator==(const Format& lhs, const Format& rhs);
bool operator!=(const Format& lhs, const Format& rhs);

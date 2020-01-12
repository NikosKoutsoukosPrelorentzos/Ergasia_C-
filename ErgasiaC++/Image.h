#pragma once

#include "array2D.h"
#include "vec3.h"
#include "imageio.h"
#include <string>

using namespace math;
using namespace image;

const std::string PPM_FORMAT = "ppm";

class Image : public Array2D<Vec3<float>>, public ImageIO
{
public:
	bool load(const std::string& filename, const std::string& format);
	bool save(const std::string& filename, const std::string& format);
};

#pragma once

#include "array2D.h"
#include "vec3.h"
#include "imageio.h"

using namespace math;
using namespace image;

class Image : public Array2D<Vec3<float>>, public ImageIO
{
	bool load(const std::string& filename, const std::string& format);



	bool save(const std::string& filename, const std::string& format);


};


#include "Image.h"
#include "ppm.h"



bool Image::load(const std::string& filename, const std::string& format) {
	if (format != PPM_FORMAT) {
		return false;
	}

	int w, h;
	float* data = ReadPPM(filename.c_str(), &w, &h);
	for (int i = 0; i < (w * h * 3)-2; i += 3) {
		this->buffer.emplace_back(data[i], data[i + 1], data[i + 2]);
	}
	this->width = w;
	this->height = h;
	return true;
}

bool Image::save(const std::string& filename, const std::string& format) {
	bool result = false;
	if (format != PPM_FORMAT) {
		std::cout << "Currently we support only PPM format";
		return false;
	}
	float* image_data = new float[width*height*3];
	for (unsigned int y = 0; y < height; y ++) {
		for (unsigned int x = 0; x < width; x++) {
			Vec3<float> color = this->buffer[x + y * width];
			image_data[0 + x * 3 + y * 3 * width] = color.r;
			image_data[1 + x * 3 + y * 3 * width] = color.g;
			image_data[2 + x * 3 + y * 3 * width] = color.b;
			
			
		}
	}
	result = WritePPM(image_data, width, height, filename.c_str());
	if (!result) {
		std::cout << "sto mpaoulo";
	}
	return result;
}

//Image::PPM_FORMAT = "ppm";

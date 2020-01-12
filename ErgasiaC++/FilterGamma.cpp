#include "FilterGamma.h"
#include <cmath>

FilterGamma::FilterGamma(float gamma) : gamma(gamma) {}

void FilterGamma :: setGamma(float gamma) {
	this->gamma = gamma;
}

float FilterGamma::getGamma() const {
	return this->gamma;
}

Image FilterGamma :: operator << (const Image& image) {
	Image filteredImage(image);
	for (unsigned int y = 0; y < image.getHeight(); y++) {
		for (unsigned int x = 0; x < image.getWidth(); x++) {
			filteredImage(x, y).r = std::powf(filteredImage(x, y).r, gamma);
			filteredImage(x, y).g = std::powf(filteredImage(x, y).g, gamma);
			filteredImage(x, y).b = std::powf(filteredImage(x, y).b, gamma);
			filteredImage(x, y) = filteredImage(x, y).clampToLowerBound(0.0f);
			filteredImage(x, y) = filteredImage(x, y).clampToUpperBound(1.0f);
		}
	}
	return filteredImage;
}
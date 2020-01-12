#include "FilterLinear.h"

FilterLinear::FilterLinear(math::Vec3<float> a, math::Vec3<float> c) : a(a), c(c)
{
}

void FilterLinear::seta(const math::Vec3<float>& a) {
	this->a = a;
}
void FilterLinear::setc(const math::Vec3<float>& c) {
	this->c = c;
}

math::Vec3<float> FilterLinear::geta() const {
	return this->a;
}
math::Vec3<float> FilterLinear::getc() const {
	return this->c;
}

Image FilterLinear :: operator << (const Image& image) {

	Image filteredImage(image);
	for (unsigned int y = 0; y < image.getHeight(); y++) {
		for (unsigned int x = 0; x < image.getWidth(); x++) {
			filteredImage(x, y) = a * filteredImage(x, y) + c;
			filteredImage(x, y)=filteredImage(x, y).clampToLowerBound(0.0f);
			filteredImage(x, y)=filteredImage(x, y).clampToUpperBound(1.0f);
		}
	}
	return filteredImage;
}

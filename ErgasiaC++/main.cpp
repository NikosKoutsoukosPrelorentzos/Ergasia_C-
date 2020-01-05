#include "ppm.h"
#include "array2d.h"
#include "Image.h"
int main() {
	Image im;
	im.load("assets/Image01.ppm", "ppm");
	im.save("Image01.ppm", "ppm");
	return 0;
}
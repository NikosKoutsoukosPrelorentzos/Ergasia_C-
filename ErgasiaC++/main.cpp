#include "ppm.h"
#include "array2d.h"

int main() {
	int w, h;

	math::Array2D<int> arr(4, 5);
	math::Array2D<int> arr2 = arr;
	//image::ReadPPM("assets/Image01.ppm", &w, &h);
	float* data = image::ReadPPM("assets/Image01.ppm", &w, &h);
	image::WritePPM(data, w, h, "assets/A.ppm");
	return 0;
}
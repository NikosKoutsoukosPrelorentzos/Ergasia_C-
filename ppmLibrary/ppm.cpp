#include "ppm.h"
#include "ppmFormat.h"
#include <fstream>
#include <iostream>
#include <cstdint>


namespace image {
	using namespace std;

	float* ReadPPM(const char* filename, int* w, int* h) {
		PPM ppm;
		//imageData = new float(*w * *h);

		ifstream inputFile = ifstream(filename, std::ios_base::binary);
		if (inputFile.good()) {

			string magic;
			inputFile >> magic;

			int width;
			int height;
			int maxColor;

			inputFile >> width >> height >> maxColor;

			ppm = PPM(magic, width, height, maxColor);
			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					int8_t r, g, b;
					inputFile >> r >> g >> b;
					ppm.data[0 + i * 3 + j * 3 * width] = r / maxColor;
					ppm.data[1 + i * 3 + j * 3 * width] = g / maxColor;
					ppm.data[2 + i * 3 + j * 3 * width] = b / maxColor;
				}
			}
		}
		else {
			cout << "File not found!!!";
		}

		return ppm.data;
	}

	bool WritePPM(const float* data, int w, int h, const char* filename) {
		bool a = false;
		return a;
	}
}
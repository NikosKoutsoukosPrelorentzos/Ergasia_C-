#include "ppm.h"
#include "ppmFormat.h"
#include <fstream>
#include <iostream>
#include <cstddef>


namespace image {
	using namespace std;

	float* ReadPPM(const char* filename, int* w, int* h) {
		PPM ppm;
		//imageData = new float(*w * *h);

		ifstream inputFile = ifstream(filename);
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
					for (int c = 0; c < 3; c++) {
						uint8_t colorValue;
						inputFile >> colorValue;
						ppm.data[c + i * 3 + j * 3 * width] = colorValue * 1.0f / maxColor;
					}
				}
			}
		}
		else {
			cout << "File not found!!!";
		}

		cout << "File was read successfully" << endl;
		return ppm.data;
	}

	bool WritePPM(const float* data, int w, int h, const char* filename) {
		bool a = false;
		return a;
	}
}
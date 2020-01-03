#include "ppm.h"
#include <fstream>
#include <iostream>
#include <cstdint>


namespace image {
	using namespace std;

	float* ReadPPM(const char* filename, int* w, int* h) {
		PPM ppm;
	
		*w = 0;
		*h = 0;

		ifstream inputFile = ifstream(filename, std::ios_base::binary);
		if (inputFile.good()) {

			string magic;
			inputFile >> magic;

			int width;
			int height;
			int maxColor;

			inputFile >> width >> height >> maxColor;
			*w = width;
			*h = height;

			ppm = PPM(magic, width, height, maxColor);
			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					uint8_t r, g, b;
					inputFile >> r >> g >> b;
					ppm.data[0 + i * 3 + j * 3 * width] = 1.0f * r / maxColor;
					ppm.data[1 + i * 3 + j * 3 * width] = 1.0f * g / maxColor;
					ppm.data[2 + i * 3 + j * 3 * width] = 1.0f * b / maxColor;
				}
			}
		}
		else {
			cout << "File not found!!!";
			return nullptr;
		}
		return ppm.data;
	}

	bool WritePPM(const float* data, int w, int h, const char* filename) {
		ofstream outputFile = ofstream(filename, std::ios_base::binary);
		bool flag;
		if (outputFile.is_open()) {
			int MAX_COLOR = 255;
			const string MAGIC = "P6";
			outputFile << MAGIC << '\n';
			outputFile << w << '\n';
			outputFile << h << '\n';
			outputFile << MAX_COLOR << '\n';

			for (int j = 0; j < h; j++) {
				for (int i = 0; i < w; i++) {
					uint8_t r = data[0 + i * 3 + j * 3 * w] * MAX_COLOR;
					uint8_t intR =static_cast<uint8_t> (static_cast<int>(r));
					uint8_t g = data[1 + i * 3 + j * 3 * w] * MAX_COLOR;
					uint8_t intG = static_cast<uint8_t> (static_cast<int>(g));
					uint8_t b = data[2 + i * 3 + j * 3 * w] * MAX_COLOR;
					uint8_t intB =static_cast<uint8_t> (static_cast<int>(b));
					outputFile <<  intR << intG << intB;
				}
				outputFile<< '\n';
			}
			flag = true;
		}
		else {
			std::cout << "mpoulo";
			flag = false;
		}
		return flag;
	}

	PPM::PPM() {}

	PPM::PPM(string magic, int width, int height, int maxColor) : magic(magic), width(width), height(height), maxColor(maxColor) {
		this->data = new float[width * height * 3];
	}

}
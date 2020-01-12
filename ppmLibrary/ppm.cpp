#include "ppm.h"
#include <fstream>
#include <iostream>
#include <cstdint>


namespace image {
	using namespace std;

	float* ReadPPM(const char* filename, int* w, int* h) {
		*w = 0;
		*h = 0;

		ifstream inputFile = ifstream(filename, std::ios::binary | std::ios::in);
		if (inputFile.good()) {

			string magic;
			inputFile >> magic;
			if (magic != P6_FORMAT) {
				throw std::exception("We support only P6 format!");
			}

			int width;
			int height;
			inputFile >> width >> height;
			if (width <= 0 || height <= 0) {
				throw std::exception("Dimensions are wrong!");
			}

			int maxColor;
			inputFile >> maxColor;
			if (maxColor < 0 || maxColor > MAX_COLOR) {
				throw std::exception("Max color over 255 is not supported!");
			}

			char newLine;
			inputFile.read(&newLine, sizeof(char)); // Reads newline character because we are in binary mode

			*w = width;
			*h = height;
			float* data = new float[width * height * 3];

			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					uint8_t r, g, b;
					inputFile.read((char*)&r,sizeof(uint8_t));
					inputFile.read((char*)&g, sizeof(uint8_t));
					inputFile.read((char*)&b,sizeof(uint8_t));
					data[0 + i * 3 + j * 3 * width] = 1.0f * r / maxColor;
					data[1 + i * 3 + j * 3 * width] = 1.0f * g / maxColor;
					data[2 + i * 3 + j * 3 * width] = 1.0f * b / maxColor;
				}
			}
			inputFile.close();
			return data;
		}
		else {
			throw std::exception("Cannot open input file!");
		}
	}

	bool WritePPM(const float* data, int w, int h, const char* filename) {
		ofstream outputFile = ofstream(filename, std::ios::binary | std::ios::out);
		bool flag;
		if (outputFile.is_open()) {
			outputFile << P6_FORMAT << '\n';
			outputFile << w << '\n';
			outputFile << h << '\n';
			outputFile << MAX_COLOR << '\n';

			for (int j = 0; j < h; j++) {
				for (int i = 0; i < w; i++) {
					int r = round(data[0 + i * 3 + j * 3 * w] * MAX_COLOR);
					int g = round(data[1 + i * 3 + j * 3 * w] * MAX_COLOR);
					int b = round(data[2 + i * 3 + j * 3 * w] * MAX_COLOR);
					uint8_t intR = static_cast<uint8_t> ((r));
					uint8_t intG = static_cast<uint8_t> ((g));
					uint8_t intB = static_cast<uint8_t> ((b));
					outputFile.write((char*)&intR, sizeof(char));
					outputFile.write((char*)&intG, sizeof(char));
					outputFile.write((char*)&intB, sizeof(char));
				}
			}
			flag = true;
		}
		else {
			cout << "Cannot open output file!" << endl;
			flag = false;
		}
		outputFile.close();
		return flag;
	}
}
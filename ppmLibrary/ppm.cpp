#include "ppm.h"
#include "ppmFormat.h"
#include <fstream>
#include <iostream>
#include <cstddef>

using namespace std;

namespace image {

	float* ReadPPM(const char* filename, int* w, int* h) {
		PPM ppm;

		ifstream inputFile = ifstream(filename, std::ios::binary | std::ios::in);
		if (inputFile.good()) {

			string magic;
			inputFile >> magic;

			int width;
			int height;
			int maxColor;
			char nl;

			inputFile >> width >> height >> maxColor;
			inputFile.read((char*)&nl, sizeof(nl));
			*w = width;
			*h = height;

			ppm = PPM(magic, width, height, maxColor);
			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					for (int c = 0; c < 3; c++) {
						uint8_t colorValue;
						inputFile.read((char*)&colorValue, sizeof(colorValue));
						ppm.data[c + i * 3 + j * 3 * width] = (colorValue * 1.0f) / maxColor;
					}
				}
			}
		}
		else {
			cout << "File not found!!!";
		}
		inputFile.close();
		cout << "File was read successfully" << endl;

		return ppm.data;
	}

	bool WritePPM(const float* data, int w, int h, const char* filename) {
		bool success = false;

		ofstream outputFile = ofstream(filename, std::ios::binary | std::ios::out);
		if (outputFile.is_open()) {
			const string MAGIC = "P6";
			const int MAX_COLOR = 255;

			outputFile << MAGIC << '\n';
			outputFile << w << '\n';
			outputFile << h << '\n';
			outputFile << MAX_COLOR << '\n';

			for (int j = 0; j < h; j++)
			{
				for (int i = 0; i < w; i++)
				{
					for (int c = 0; c < 3; c++)
					{
						uint8_t ch = static_cast<uint8_t>(round(MAX_COLOR * data[c + i * 3 + j * 3 * w]));
						outputFile.write((char*)&ch, sizeof(ch));
					}
				}
			}
			success = true;
		}
		else {
			success = false;
			std::cerr << "Could not write to file successfully" << std::endl;
		}
		outputFile.close();
		return success;
	}
}
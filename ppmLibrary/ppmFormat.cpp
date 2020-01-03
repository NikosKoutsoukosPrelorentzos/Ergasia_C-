#include "ppmFormat.h"

PPM::PPM() : magic(""), width(0), height(0), maxColor(0), data(nullptr) {}

PPM::PPM(string magic, int width, int height, int maxColor) : magic(magic), width(width), height(height), maxColor(maxColor) {
	this->data = new float[width * height * 3];
}
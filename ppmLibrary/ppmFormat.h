#pragma once

#include<string>

using namespace std;

struct PPM
{
	PPM();
	PPM(string magic, int width, int height, int maxColor);
	string magic;
	int width;
	int height;
	int maxColor;
	float* data;
};
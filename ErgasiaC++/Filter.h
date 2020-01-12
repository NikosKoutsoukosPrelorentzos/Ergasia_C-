#pragma once
#include "Image.h"
class Filter
{
public:
	virtual Image operator << (const Image& image) = 0;
};
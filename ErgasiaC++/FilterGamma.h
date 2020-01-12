#pragma once
#include "Filter.h"
class FilterGamma : public Filter
{
private:
	float gamma;
public:
	FilterGamma(float gamma);
	void setGamma(float gamma);
	float getGamma() const;
	virtual Image operator << (const Image& image);
};


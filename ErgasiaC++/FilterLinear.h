#pragma once
#include "Filter.h"
#include "vec3.h"

class FilterLinear : public Filter
{
private:
	math::Vec3<float> a, c;
public:
	FilterLinear(math::Vec3<float> a, math::Vec3<float> c);
	void seta(const math::Vec3<float>& a);
	void setc(const math::Vec3<float>& c);

	math::Vec3<float> geta() const;
	math::Vec3<float> getc() const;


	virtual Image operator << (const Image& image);
};


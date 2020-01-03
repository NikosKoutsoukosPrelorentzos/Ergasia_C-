#pragma once
#include "array2d.h"

namespace math
{
	template<typename T>
	const unsigned int Array2D<T>::getWidth() const
	{
		return width;
	}

	template<typename T>
	inline const unsigned int Array2D<T>::getHeight() const
	{
		return height;
	}

	template<typename T>
	inline T* Array2D<T>::getRawDataPtr()
	{
		return &buffer;
	}

	template<typename T>
	inline void Array2D<T>::setData(const T* const& data_ptr)
	{
		if (height == 0 || width == 0) {
			std::cout << "Dimensions are zero" << std::endl;
			exit(1);
		}
		else {
			buffer.resize(width * height);
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {

					buffer[x + y * width] = data_ptr[x + y * width];
				}
			}
		}
	}

	template<typename T>
	inline T& Array2D<T>::operator()(unsigned int x, unsigned int y)
	{
		return buffer[x + y * width];
	}

	template<typename T>
	inline Array2D<T>::Array2D(unsigned int width, unsigned int height, const T* data_ptr) : width(width), height(height)
	{
		buffer.resize(width * height);
		if (data_ptr != nullptr)
		{
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {

					buffer[x + y * width] = data_ptr[x + y * width];
				}
			}
		}
	}

	template<typename T>
	inline Array2D<T>::Array2D(const Array2D<T>& src)
	{
		this->width = src.getWidth();
		this->height = src.getHeight();
		this->setData(&src.buffer[0]);

	}

	template<typename T>
	inline Array2D<T>::~Array2D()
	{
	}

	template<typename T>
	inline Array2D<T>& Array2D<T>::operator=(const Array2D& right)
	{
		this->width = right.getWidth();
		this->height = right.getHeight();
		this->setData(&right.buffer[0]);

		return *this;
		// TODO: insert return statement here
	}

}

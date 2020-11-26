#pragma once

#include <vector>
#include <iostream>
#include <cmath>

class Filter
{
	public:
		Filter();
		~Filter();

		void gaussian(int size, int sigma);
		void sobel_v();
		void sobel_h();

		void apply(int width, int height, int numChannels, unsigned char* front, unsigned char* back);

	private:

		float pi;
		float e;

		int size;
		float* kernel;
};

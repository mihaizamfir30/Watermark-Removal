#pragma once

#include <vector>
#include <iostream>
#include <cmath>

#include "lodepng.h"

class Image
{
	public:
		Image();
		~Image();

		void open(const char* filename);
		void write(const char* filename);

		void gaussian(int size, int sigma);

		void modify();

		void convertToGreyscale();

		unsigned char rgb2gray(unsigned char* color);

		unsigned int width;
		unsigned int height;
		unsigned int numChannels;

		unsigned char* front;
		unsigned char* back;

		void swap();

	private:


		float pi;
		float e;


		std::vector<unsigned char> image; //the raw pixels


};

#include "Filter.h"

Filter::Filter() {

	pi = 3.14159265359;
	e = 2.71828;

}

Filter::~Filter() {

}


void Filter::gaussian(int size, int sigma) {

	this->size = size;
	kernel = (float*)malloc(size * size * sizeof(float));

	int hsize = (int)(size / 2) ;
	float normal = 1.0 / (2.0 * pi * pow(sigma, 2));

	for (int x = -hsize; x < hsize + 1; x++)
	{
		int i = x + hsize;

		for (int y = -hsize; y < hsize + 1; y++)
		{
			int j = y + hsize;

			float val = pow(e, -((pow(x, 2) + pow(y, 2)) / (2.0 * pow(sigma, 2)))) * normal;
			kernel[i * size + j] = val;
		}
	}
}

void Filter::sobel_v() {
	size = 3;
	kernel = (float*)malloc(size * size * sizeof(float));

	kernel[0] =  1;		kernel[1] =  2;		kernel[2] =  1;
	kernel[3] =  0;		kernel[4] =  0;		kernel[5] =  0;
	kernel[6] = -1;		kernel[7] = -2;		kernel[8] = -1;
}

void Filter::sobel_h() {
	size = 3;
	kernel = (float*)malloc(size * size * sizeof(float));

	kernel[0] = -1;		kernel[1] = 0;		kernel[2] = 1;
	kernel[3] = -2;		kernel[4] = 0;		kernel[5] = 2;
	kernel[6] = -1;		kernel[7] = 0;		kernel[8] = 1;
}

void Filter::apply(int width, int height, int numChannels, unsigned char* front, unsigned char* back) {

	int i = 0;
	int j = 0;

	for (int x = 0; x < width * height * numChannels; x += numChannels)
	{
		back[x] = front[x];
		back[x + 1] = front[x + 1];
		back[x + 2] = 255;
		back[x + 3] = front[x + 3];
	}

}

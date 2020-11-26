#pragma once

#include <ctime>
#include <iostream>

using namespace std;

#include <stdio.h>  /* defines FILENAME_MAX */

#include <stdlib.h>

#define WINDOWS

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include "Image.h"
#include "Filter.h"

#include "lodepng.h"

std::vector<unsigned char> decodeOneStep(const char* filename, unsigned *width, unsigned *height) {
	std::vector<unsigned char> image; //the raw pixels
	//unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, *width, *height, filename);

	//if there's an error, display it
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
	return image;
}

void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
	/*Encode the image*/
	unsigned error = lodepng_encode32_file(filename, image, width, height);

	/*if there's an error, display it*/
	if (error) printf("error %u: %s\n", error, lodepng_error_text(error));
}

int main(int argc, char **argv)
{

	Image img = Image();

	img.open("image.png");

	img.convertToGreyscale();

	/*
	Filter sobel_v = Filter();
	sobel_v.sobel_v();

	sobel_v.apply(img.width, img.height, img.numChannels, img.front, img.back);
	img.swap();
	*/

	//return 0;
	//img.modify();

	img.write("image_final.png");

	return 0;
}
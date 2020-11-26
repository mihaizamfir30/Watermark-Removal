#include "Image.h"

Image::Image() {

	pi = 3.14159265359;
	e = 2.71828;

}

Image::~Image() {

}

void Image::open(const char* filename) {

	numChannels = 4;

	std::cout << width << " " << height << std::endl;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	std::cout << width << " " << height << std::endl;

	//if there's an error, display it
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	front = image.data();

	back = (unsigned char*)malloc(width * height * numChannels * sizeof(unsigned char));
}

void Image::write(const char* filename) {

	/*Encode the image*/
	unsigned error = lodepng_encode32_file(filename, front, width, height);

	/*if there's an error, display it*/
	if (error) printf("error %u: %s\n", error, lodepng_error_text(error));
}

void Image::gaussian(int size, int sigma) {

	int hsize = (int)(size / 2) ;

	float normal = 1.0 / (2.0 * pi * pow(sigma, 2));

	float* kernel = (float*)malloc(size * size * sizeof(float));

	for (int x = -hsize; x < hsize + 1; x++)
	{

		int i = x + hsize;

		for (int y = -hsize; y < hsize + 1; y++)
		{
			//val = np.exp(-((x * *2 + y * *2) / (2.0 * sigma * *2))) * normal

			int j = y + hsize;

			float val = pow(e, -((pow(x, 2) + pow(y, 2)) / (2.0 * pow(sigma, 2)))) * normal;

			//float val = pow(e, -(pow(i, 2) + pow(j, 2)) / (2.0 * pow(sigma, 2))) * normal;

			kernel[i * size + j] = val;

			//std::cout << i * size + j << " ";

			std::cout << kernel[i * size + j] << " ";

		}

		std::cout << std::endl;
	}
}

void Image::swap() {

	unsigned char* aux = front;
	front = back;
	back = aux;
}

unsigned char Image::rgb2gray(unsigned char* color) {
	return color[0] * 0.3 + color[1] * 0.59 + color[2] * 0.11;
}


void Image::convertToGreyscale() {

	for (int x = 0; x < width * height * numChannels; x += numChannels) {
		front[x] = rgb2gray(&front[x]);// front[x] * 0.3 + front[x + 1] * 0.59 + front[x + 2] * 0.11;
		front[x + 1] = front[x];
		front[x + 2] = front[x];
	}
}

void Image::modify() {

	for (int x = 0; x < width * height * numChannels; x += numChannels)
	{

		int i = 0;
		int j = 0;

		std::cout << i << " " << j << std::endl;

		back[x] = front[x];
		back[x + 1] = front[x + 1];
		back[x + 2] = 255;
		back[x + 3] = front[x + 3];
	}

	swap();
}

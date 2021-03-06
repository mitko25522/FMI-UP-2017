#include "stdafx.h"
#include <iostream>
#include "Bitmap.h"
#include "Functions.h"

using namespace std;

#define INPUT_IMAGE_NAME "test.bmp"
#define MODIFIED_IMAGE_NAME "test_new.bmp"

void plugPixelsIn2dArray(unsigned container[MAX_SIZE_2D][MAX_SIZE_2D], unsigned image[MAX_SIZE], unsigned width, unsigned height);

int main()
{
	

	unsigned int width, height, image[MAX_SIZE], container[MAX_SIZE_2D][MAX_SIZE_2D];

	int rval;
	rval = LoadBitmap(INPUT_IMAGE_NAME, image, MAX_SIZE, width, height);

	if (rval != ALL_OK)
	{
		std::cerr << "Cannot load image data from test.bmp! Error code " << rval << "\n";
		return 1;
	}

	plugPixelsIn2dArray(container, image, width, height);
	//identifyImage(container, width, height);
	identifyImage(container, width, height);
	changeOneRow(container, width, height);
	changeOneCol(container, width, height);
	revert2dArray(container, image, width, height);
	

	rval = SaveBitmap(MODIFIED_IMAGE_NAME, image, width, height);

	if (rval != ALL_OK)
	{
		std::cerr << "Cannot save image data to test_new.bmp! Error code " << rval << "\n";
		return 2;
	}

	return 0;
}


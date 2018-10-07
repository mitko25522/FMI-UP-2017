#pragma once
#include <iostream>
#define WHITE 0xFFFFFFFF
using namespace std;

extern const int MAX_SIZE = 100000;
extern const int MAX_SIZE_2D = 315;

struct ArrayLocation
{
	int row;
	int column;
};
struct ImageLocation {
	ArrayLocation upperLeft;
	ArrayLocation lowerLeft;
	ArrayLocation upperRight;
	ArrayLocation lowerRight;
};

void plugPixelsIn2dArray(unsigned container[MAX_SIZE_2D][MAX_SIZE_2D], unsigned image[MAX_SIZE], unsigned width, unsigned height) {
	int s = 0;
	for (int i = 0; i < int(height); i++) {
		for (int j = 0; j < int(width); j++) {
			container[i][j] = image[s];
			s++;
		}
	}
}

void identifyImage(unsigned container[MAX_SIZE_2D][MAX_SIZE_2D], unsigned width, unsigned height) {
	ImageLocation imageLocation;
	int currentDistance;
	int minimumDistance = width;
	for (int i = 0; i<int(height); i++) {
		for (int j = 0; j<int(width); j++) {
			if (container[i][j] != WHITE) {
				currentDistance = j;
				if (minimumDistance > currentDistance) {
					minimumDistance = currentDistance;
				}
				break;
			}
		}
	}
	imageLocation.lowerLeft.column = minimumDistance;
	imageLocation.upperLeft.column = minimumDistance;
	cout << minimumDistance << "th column is the smallest distance between the left wall and the image\n";

	minimumDistance = height;
	for (int j = 0; j<int(width); j++) {
		for (int i = 0; i<int(height); i++) {
			if (container[i][j] != WHITE) {
				currentDistance = i;
				if (minimumDistance > currentDistance) {
					minimumDistance = currentDistance;
				}
			}
		}
	}
	imageLocation.lowerLeft.row = minimumDistance;
	imageLocation.lowerRight.row = minimumDistance;
	cout << minimumDistance << "th row is the smallest distance between bottom wall and the image\n";
	//return imageLocation;
}

void revert2dArray(unsigned container[MAX_SIZE_2D][MAX_SIZE_2D], unsigned image[MAX_SIZE], unsigned width, unsigned height) {
	int s = 0;
	for (int i = 0; i < int(height); i++) {
		for (int j = 0; j < int(width); j++) {
			image[s] = container[i][j];
			s++;
		}
	}
}

void changeOneRow(unsigned container[MAX_SIZE_2D][MAX_SIZE_2D], unsigned width, unsigned height) {
		//debugging purpose
		for (int j = 0; j < int(width); j++) {
			container[j][23] = 0xFF0000;
		}
	
}

void changeOneCol(unsigned container[MAX_SIZE_2D][MAX_SIZE_2D], unsigned width, unsigned height) {
	//debugging purpose
	for (int j = 0; j < int(width); j++) {
		container[31][j] = 0xFF0000;
	}
}

#include "stdafx.h"
#include <iostream>
using namespace std;
const int MAXIMUM_SIZE = 10;

void fillArray(int square[MAXIMUM_SIZE][MAXIMUM_SIZE], int size);
bool checkRequirements(const int square[MAXIMUM_SIZE][MAXIMUM_SIZE], const int size);
int main() {
	int square[MAXIMUM_SIZE][MAXIMUM_SIZE];
	int sizeOfSquare;
	do {
		cout << "Enter size of square: ";
		cin >> sizeOfSquare;
	}
	while (sizeOfSquare < 0 || sizeOfSquare>10);
	fillArray(square, sizeOfSquare);
	if (checkRequirements(square, sizeOfSquare)) {
		cout << "It is a magical square\n";
	}
	else cout << "It's not a magical square\n";
	return 0;
}

void fillArray(int square[MAXIMUM_SIZE][MAXIMUM_SIZE], int size) {
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			cin >> square[row][col];
		}
	}
}
bool checkRequirements(const int square[MAXIMUM_SIZE][MAXIMUM_SIZE], const int size) {
	int currentRowSum = 0;
	int lastRowSum = 0;
	int currentColumnSum = 0;
	int lastColumnSum = 0;
	int diagonalOneSum = 0;
	int diagonalTwoSum = 0;

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			currentRowSum += square[row][col];
		}
		if (lastRowSum == 0) {
			lastRowSum = currentRowSum;
		}
		else {
			if (currentRowSum != lastRowSum) {
				return false;
			}
		}
		currentRowSum = 0;
	}

	for (int col = 0; col < size; col++){
		for (int row = 0; row < size; row++) {
			currentColumnSum += square[row][col];
		}
		if (lastColumnSum == 0) {
			lastColumnSum = currentColumnSum;
		}
		else {
			if (lastColumnSum != currentColumnSum) {
				return false;
			}
		}
		currentColumnSum = 0;
	}

	for (int index = 0; index < size; index++) {
		diagonalOneSum += square[index][index];
	}

	for (int col = size - 1 , row = 0; (col >= 0) && (row < size); col--, row++) {
			diagonalTwoSum += square[row][col];
	}
	if ((lastRowSum != lastColumnSum) || (lastRowSum != diagonalOneSum) || (lastRowSum != diagonalTwoSum)) {
		return false;
	}
	else return true;
}
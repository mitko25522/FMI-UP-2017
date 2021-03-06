#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;

int swapBytes(int source, int startingFromIndex, int length, bool isStartingWithZero);

int main() {
	int resultContainer = 0;
	int inputNumber = 60;
    int sizeOfIntInBits = sizeof(int) * 8;
	for (int observedBitIndex = 0; observedBitIndex < sizeOfIntInBits; observedBitIndex++) {
		int bitmask = 0x1;
		bitmask =  bitmask << observedBitIndex;//shift bitmask observedBitIndex times to the left so that we can check if the current bit is one without changing the number
		bool currentBitIsOne = ((inputNumber & bitmask) == bitmask);
		int lengthOfPattern = 0; // this will mark how much of the left are like the "currentBit"
		for (int remainingBitsIndex = observedBitIndex + 1; remainingBitsIndex < sizeOfIntInBits; remainingBitsIndex++) {

			// check if currentRemaining bit is one
			bitmask = 0x1;
			bitmask = bitmask << remainingBitsIndex;
			bool currentRemainingBitIsOne = ((inputNumber & bitmask) == bitmask);
			if ((currentBitIsOne && currentRemainingBitIsOne) || ((!currentBitIsOne) && (!currentRemainingBitIsOne))) {
				lengthOfPattern++;
			}
			else if ((!currentBitIsOne && currentRemainingBitIsOne) || ((currentBitIsOne) && (!currentRemainingBitIsOne))) {
				cout << " pattern starts at " << observedBitIndex << " and is " << lengthOfPattern << " bits long" << endl;
				resultContainer = resultContainer | swapBytes(inputNumber, observedBitIndex, lengthOfPattern, currentBitIsOne);
				observedBitIndex += lengthOfPattern;
				break;
			}
		}
	}
	
	cout << resultContainer << endl;
	system("pause");
	return 0;
}

int swapBytes(int source, int startingFromIndex, int length, bool isCurrentBitOne) {
	int result = 0;
	int helperSwapIndex = 0;
	for (int i = startingFromIndex + length; i >= startingFromIndex; i--) {
		if (helperSwapIndex % 2 == (isCurrentBitOne ? 1 : 0)) {
			int bitShiftHelper = 0x1;
			result = result | (source ^ (bitShiftHelper << i + 1));
	}
		helperSwapIndex++;
	}
	return result;
}

#include <iostream>
using namespace std;

void findBracketIndexes(char * container, int &openingBracketIndex, int &closingBracketIndex);
int findMultiplier(char * container, int openingBracketIndex, int &numberOFDigits);
bool isNumber(int number);
bool bracketsRemain(char * container);
int countLettersInBrackets(int openingBracketIndex, int closingBracketIndex);
void decompressCurrentBrackets(char * container, char * tempContainer, int openingBracketIndex, int closingBracketIndex, int numberOfDigits, int multiplier);
void copyValues(char * tempContainer, char * container);
bool bracketAmountIsIncorrect(char * container);
size_t strlen(const char * text);
void removeBrackets(char *& container, int currentSize);
void getInput(char *& array);
void checkAllocation(char * array);
void checkBrackets(char * array);
void printCharArr(char * array);


int main() {
	char * compressedCharArr = new (nothrow) char[1000];
	checkAllocation(compressedCharArr);

	getInput(compressedCharArr);
	int currentSize = strlen(compressedCharArr);
	char * container = new (nothrow) char[currentSize + 1];
	checkAllocation(container);
	copyValues(compressedCharArr, container);
	delete[] compressedCharArr;

	checkBrackets(container);
	removeBrackets(container, currentSize);

	printCharArr(container);
	delete[] container;
	return 0;
}


void findBracketIndexes(char * container, int &openingBracketIndex, int &closingBracketIndex) {
	for (int i = 0; container[i] != '\0'; i++) {
		if (container[i] == 40) {
			openingBracketIndex = i;
		}
		if (container[i] == 41) {
			closingBracketIndex = i;
			break;
		}
	}
}

int findMultiplier(char * container, int openingBracketIndex, int &numberOfDigits) {
	int multiplier = 0;
	numberOfDigits = 0;
	for (int i = openingBracketIndex - 1, j = 1; isNumber(container[i]); i--, j *= 10) {
		multiplier += (container[i] - '0') * j;
		numberOfDigits++;
	}
	return multiplier;
}

bool isNumber(int number) {
	if (number >= 48 && number <= 57) {
		return true;
	}
	else return false;
}

bool bracketsRemain(char * container) {
	for (int i = 0; container[i] != '\0'; i++) {
		if ((container[i] == '(') || (container[i] == ')')) {
			return true;
		}
	}
	return false;
}

int countLettersInBrackets(int openingBracketIndex, int closingBracketIndex) {
	int numberOfLetters = closingBracketIndex - openingBracketIndex - 1;
	return numberOfLetters;
}

void decompressCurrentBrackets(char * container, char * tempContainer, int openingBracketIndex, int closingBracketIndex, int numberOfDigits, int multiplier) {
	int i;
	
	for (i = 0; i < openingBracketIndex - numberOfDigits; i++) {
		tempContainer[i] = container[i];
	}

	while (multiplier > 0) {
		for (int j = openingBracketIndex + 1; j < closingBracketIndex; j++) {
			tempContainer[i] = container[j];
			i++;
		}
		multiplier--;
	}

	for (int j = closingBracketIndex + 1; container[j] != '\0'; j++) {
		tempContainer[i] = container[j];
		i++;
	}

	tempContainer[i] = '\0';
}

//copies values from containerOne to containerTwo
void copyValues(char * containerOne, char * containerTwo) {
	for (int i = 0; containerOne[i] != '\0'; i++) {
		containerTwo[i] = containerOne[i];
		if (containerOne[i + 1] == '\0') {
			containerTwo[i + 1] = '\0';
		}
	}
}

//counts number of opening and closing brackets
bool bracketAmountIsIncorrect(char * container) {
	int openingBrackets = 0;
	int closingBrackets = 0;
	for (int i = 0; container[i] != '\0'; i++) {
		if (container[i] == 40) {
			openingBrackets++;
		}
		else if (container[i] == 41) {
			closingBrackets++;
		}
	}

	if (openingBrackets != closingBrackets) {
		return true;
	}
	else return false;
}

size_t strlen(const char* text) {
	size_t length = 0;
	while (text[length])
		++length;
	return length;
}

//recursive function that decompresses the string
void removeBrackets(char *& container, int currentSize) {
	static int previousSize;
	if (!bracketsRemain(container)) { return; }
	int openingBracketIndex, closingBracketIndex, numberOfDigits;
	findBracketIndexes(container, openingBracketIndex, closingBracketIndex);
	int multiplier = findMultiplier(container, openingBracketIndex, numberOfDigits);
	int lettersInBrackets = countLettersInBrackets(openingBracketIndex, closingBracketIndex);
	previousSize = currentSize;
	currentSize = previousSize - 2 - lettersInBrackets - numberOfDigits + multiplier * lettersInBrackets;
	char * tempContainer = new (nothrow) char[currentSize + 1];
	checkAllocation(tempContainer);
	decompressCurrentBrackets(container, tempContainer, openingBracketIndex, closingBracketIndex, numberOfDigits, multiplier);
	delete[] container;
	container = new (nothrow) char[currentSize + 1];
	checkAllocation(container);
	copyValues(tempContainer, container);
	delete[] tempContainer;
	removeBrackets(container, currentSize);
}

void getInput(char *& array) {
	cout << "Type in some input text: ";
	cin >> array;

}

void checkAllocation(char * array) {
	if (!array) {
		cout << "Error allocating memory, terminating process\n";
		exit(1);
	}
}

void checkBrackets(char * array) {
	if (bracketAmountIsIncorrect(array)) {
		cout << "Incorrectly inputed brackets\n";
		exit(1);
	}
}

void printCharArr(char * array) {
	for (int i = 0; array[i] != '\0'; i++) {
		cout << array[i];
	}
}
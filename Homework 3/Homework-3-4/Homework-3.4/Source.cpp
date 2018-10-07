#include <iostream>
#include <vld.h>
using namespace std;


struct String
{
	char * letter = new char[100];
	bool exists = false;

	void fillAndFixSize() {
		cin >> letter;
		fixSize();
	}

	void fixSize() {
		size_t length = strlen(letter);
		char * tempWord = new char[length + 1];
		for (int i = 0; letter[i] != '\0'; i++) {
			tempWord[i] = letter[i];
			if (letter[i + 1] == '\0')
				tempWord[i + 1] = '\0';
		}
		delete[] letter;
		letter = new char[length + 1];

		for (int i = 0; tempWord[i] != '\0'; i++) {
			letter[i] = tempWord[i];
			if (tempWord[i + 1] == '\0')
				letter[i + 1] = '\0';
		}
		delete[] tempWord;
	}

	bool isValid() {
		if ((strlen(letter) < 2) || (strlen(letter) > 40))
		{
			return false;
		}
		else {
			return true;
		}
	}

	void dispose() {
		delete[] letter;
	}
};

size_t strlen(const char * text);
int getCountInput();
void separateWords(String * crosswordWords, char ** crossword, const size_t rows, const size_t columns, const size_t inputWordsCount);
bool isLetter(const int character);
String * getInputWords(const size_t count);
void cleanUpStringMemory(String * inputWords, const size_t count);
bool inputWordsAreInvalid(String * inputWords, const size_t count);
size_t getRowsValue();
size_t getColumnsValue();
size_t getValue();
bool rowsOrColsAreInvalid(const size_t rows, const size_t columns);
bool countIsInvalid(const int count);
void fillTwoDimArr(char ** crossword, const size_t rows, const size_t columns);
char ** initializeTwoDimArr(const size_t rows, const size_t columns);
bool compareStringContainers(const String * stringOne, const String * stringTwo, const size_t countOfWordsInStringOne, const size_t countOfWordsInStringTwo);
bool compareWords(const char * wordOne, const char * wordTwo);
size_t countCrosswordWords(const String * crosswordWords);
bool inputIsInvalid(const size_t rows, const size_t columns, String * inputWords, int inputWordsCount);
void cleanUpTwoDimArrMemory(char ** arr, const size_t rows);
void printResult(const bool result);

int main() {
	int inputWordsCount = getCountInput();
	if (countIsInvalid(inputWordsCount)) { return -1; }

	String * inputWords = getInputWords(inputWordsCount);
	const size_t rows = getRowsValue();
	const size_t columns = getColumnsValue();
	if (inputIsInvalid(rows, columns, inputWords, inputWordsCount)) { return -1; }

	char ** crossword = initializeTwoDimArr(rows, columns);
	fillTwoDimArr(crossword, rows, columns);
	size_t crosswordWordsSize = rows * columns;
	String * crosswordWords = new String[crosswordWordsSize]; //MUST FIX - incorrect size becouse you can have more words than the product of the rows and columns by using '*'
	separateWords(crosswordWords, crossword, rows, columns, inputWordsCount);
	size_t crosswordWordsCount = countCrosswordWords(crosswordWords);

	bool result = compareStringContainers(crosswordWords, inputWords, crosswordWordsCount, inputWordsCount);
	printResult(result);
	cleanUpStringMemory(inputWords, inputWordsCount);
	cleanUpStringMemory(crosswordWords, crosswordWordsSize);
	cleanUpTwoDimArrMemory(crossword, rows);
	return 0;
}

size_t strlen(const char* text) {
	size_t length = 0;
	while (text[length]) {
		length++;
	}
	return length;
}

//spaghetti code function sorry
void separateWords(String * crosswordWords, char ** crossword, const size_t rows, const size_t columns, const size_t inputWordsCount) {
	static int index = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if ((isLetter(crossword[i][0])) && isLetter(crossword[i][1])) {
				for (int g = j, p = 0; ((g < columns) && (crossword[i][g] != '*')); g++, p++) {
					crosswordWords[index].letter[p] = crossword[i][g];
					j = g;
					if ((g + 1 == columns) || (crossword[i][g + 1] == '*')) {
						crosswordWords[index].letter[p + 1] = '\0';
						crosswordWords[index].exists = true;
						index++;
					}
				}
			}
			if ((crossword[i][j] == '*') && (isLetter(crossword[i][j + 1])) && (isLetter(crossword[i][j + 2]))) {
				for (int g = j + 1, p = 0; ((g < columns) && (crossword[i][g] != '*')); g++, p++) {
					crosswordWords[index].letter[p] = crossword[i][g];
					j = g;
					if ((g + 1 == columns) || (crossword[i][g + 1] == '*')) {
						crosswordWords[index].letter[p + 1] = '\0';
						crosswordWords[index].exists = true;
						index++;
					}
				}
			}
		}
	}

	for (int j = 0; j < columns; j++) {
		for (int i = 0; i < rows - 2; i++) {
			if ((isLetter(crossword[0][j])) && isLetter(crossword[1][j])) {
				for (int g = i, p = 0; ((g < rows) && (crossword[g][j] != '*')); g++, p++) {
					crosswordWords[index].letter[p] = crossword[g][j];
					i = g;
					if ((g + 1 == rows) || (crossword[g + 1][j] == '*')) {
						crosswordWords[index].letter[p + 1] = '\0';
						crosswordWords[index].exists = true;
						index++;
					}
				}
			}
			if ((crossword[i][j] == '*') && (isLetter(crossword[i + 1][j])) && (isLetter(crossword[i + 2][j]))) {
				for (int g = i + 1, p = 0; ((g < rows) && (crossword[g][j] != '*')); g++, p++) {
					crosswordWords[index].letter[p] = crossword[g][j];
					i = g;
					if ((g + 1 == rows) || (crossword[g + 1][j] == '*')) {
						crosswordWords[index].letter[p + 1] = '\0';
						crosswordWords[index].exists = true;
						index++;
					}
				}
			}
		}
	}

}

bool isLetter(const int character) {
	if ((character >= 65 && character <= 90) || (character >= 97 && character <= 122)) {
		return true;
	}
	else {
		return false;
	}
}

int getCountInput() {
	int count;
	cout << "Words count: ";
	cin >> count;
	return count;
}

String * getInputWords(const size_t count) {
	String * inputWords = new String[count];
	for (int i = 0; i < count; i++) {
		inputWords[i].fillAndFixSize();

	}
	return inputWords;
}

bool inputWordsAreInvalid(String * inputWords, const size_t count) {
	for (int index = 0; index < count; index++) {
		if (!inputWords[index].isValid())
			return true;
	}
	return false;
}

void cleanUpStringMemory(String * string, const size_t count) {
	for (int i = 0; i < count; i++) {
		string[i].dispose();
	}
	delete[] string;
}

size_t getRowsValue() {
	cout << "Rows: ";
	return getValue();
}

size_t getColumnsValue() {
	cout << "Columns: ";
	return getValue();
}

size_t getValue() {
	size_t value;
	cin >> value;
	return value;
}

bool rowsOrColsAreInvalid(const size_t rows, const size_t columns) {
	if (rows > 100 || rows < 0 || columns > 100 || columns < 0) {
		return true;
	}
	else {
		return false;
	}
}

bool countIsInvalid(const int count) {
	if (count < 0) {
		cout << "Invalid input\n";
		return true;
	}
	else {
		return false;
	}
}

char ** initializeTwoDimArr(const size_t rows, const size_t columns) {
	char ** crossword = new char*[rows];
	for (int index = 0; index < rows; index++) {
		crossword[index] = new char[columns];
	}
	return crossword;
}

void fillTwoDimArr(char ** crossword, const size_t rows, const size_t columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cin >> crossword[i][j];
		}
	}
}

bool compareStringContainers(const String * stringOne, const String * stringTwo, const size_t countOfWordsInStringOne, const size_t countOfWordsInStringTwo)
{
	for (int i = 0; i < countOfWordsInStringOne; i++) {
		bool isCurrentWordPresent = false;
		for (int j = 0; j < countOfWordsInStringTwo; j++) {
			if (compareWords(stringOne[i].letter, stringTwo[j].letter)) {
				isCurrentWordPresent = true;
				break;
			}
		}
		if (!isCurrentWordPresent) {
			return false;
		}
	}
	return true;
}

bool compareWords(const char * wordOne, const char * wordTwo) {
	for (int i = 0; wordOne[i] != '\0'; i++) {
		if (wordOne[i] != wordTwo[i]) {
			return false;
		}
	}
	return true;
}

size_t countCrosswordWords(const String * crosswordWords) {
	size_t count = 0;
	for (int i = 0; crosswordWords[i].exists; i++) {
		count++;
	}
	return count;
}

bool inputIsInvalid(const size_t rows, const size_t columns, String * inputWords, int inputWordsCount) {
	if (rowsOrColsAreInvalid(rows, columns) || inputWordsAreInvalid(inputWords, inputWordsCount)) {
		cout << "\nInvalid input\n";
		cleanUpStringMemory(inputWords, inputWordsCount);
		return true;
	}
	return false;
}

void cleanUpTwoDimArrMemory(char ** arr, const size_t rows) {
	for (int i = 0; i < rows; i++)
		delete[] arr[i];
	delete[] arr;
}

void printResult(const bool result) {
	if (result) {
		cout << "True\n";
	}
	else {
		cout << "False\n";
	}
}
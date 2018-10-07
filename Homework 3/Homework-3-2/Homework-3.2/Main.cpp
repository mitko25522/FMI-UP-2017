#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

void findNumberOfLetters(int &numberOfLetters, const char * pOfDesignatedWord);
void fillWithUnderscores(char * pStage, const size_t numberOfLetters);
void fillWithZeroes(char * pChosenLetters, const size_t numberOfLetters);
void printWordProgress(const char * pStage, const size_t numberOfLetters);
void printCurrentStage(int numberOfLetters, const char * pOfDesignatedWord, int &attempts, char * pStage, char * pChosenLetters, const size_t lengthOfChosenLettersArray, char * pGeneratedLetters, int gameChoice);
void printHistory(const char * pChosenLetters, const size_t lengthOfChosenLettersArray);
void checkDesignatedWord(char chosenLetter, const char * pOfDesignatedWord, const size_t numberOfLetters, char * pStage, int &attempts);
bool underscoresRemain(const char * pStage, const size_t length);
char randomInput(char * pGeneratedLetters);
bool letterAlreadySelected(const char letter, const char * pGeneratedLetters, const size_t index);
char getMistakesChoice();
int getGameChoice();
void printResult(char * pStage, int numberOfLetters, const char * words[], int attempts, int selectedNumberIndex);
void startGameLoop(int numberOfLetters, const char * pOfDesignatedWord, char * pStage, int &attempts, char * pChosenLetters, int lengthOfChosenLettersArray, char * pGeneratedLetters, int gameChoice);

#define ALPHABET_SIZE 26

int maximumMistakes = 5;

int main() {
	srand(time(NULL));
	const char * words[] = { "apple", "orange", "month", "vehicle", "tree", "success", "anticipation", "build", "constant", "limit", "approach", "edit", "crossword" };
	int selectedNumberIndex = rand() % sizeof(words) / sizeof(*words);
	char mistakesChoice = getMistakesChoice();
	int gameChoice = getGameChoice();
	int numberOfLetters = 0;
	const char * pOfDesignatedWord = &*words[selectedNumberIndex];
	findNumberOfLetters(numberOfLetters, pOfDesignatedWord);

	char * pStage = new char[numberOfLetters];
	fillWithUnderscores(pStage, numberOfLetters);
	int lengthOfChosenLettersArray = numberOfLetters + maximumMistakes;
	char * pChosenLetters = new char[lengthOfChosenLettersArray];
	fillWithZeroes(pChosenLetters, lengthOfChosenLettersArray);
	char * pGeneratedLetters = new char[ALPHABET_SIZE];
	fillWithUnderscores(pGeneratedLetters, int(ALPHABET_SIZE));

	int attempts = 1;
	startGameLoop(numberOfLetters, pOfDesignatedWord, pStage, attempts, pChosenLetters, lengthOfChosenLettersArray, pGeneratedLetters, gameChoice);
	printResult(pStage, numberOfLetters, words, attempts, selectedNumberIndex);
	cout << endl;
	delete[] pStage;
	delete[] pChosenLetters;
	delete[] pGeneratedLetters;
	return 0;
}

void findNumberOfLetters(int &numberOfLetters, const char * pOfDesignatedWord) {
	//cout << "Chosen word: "; //if you want to see the word that you are guessing uncomment this line and the line below
	for (int i = 0; *(pOfDesignatedWord + i) != '\0'; i++) {
		//cout << *(pOfDesignatedWord + i); 
		numberOfLetters++;
	}
	cout << endl;
}

void printCurrentStage(int numberOfLetters, const char * pOfDesignatedWord, int &attempts, char * pStage, char * pChosenLetters, const size_t lengthOfChosenLettersArray, char * pGeneratedLetters, int gameChoice) {
	char chosenLetter;
	cout << "[" << attempts << "/" << maximumMistakes << "] ";
	printWordProgress(pStage, numberOfLetters);
	printHistory(pChosenLetters, lengthOfChosenLettersArray);
	static int counter;
	cout << "\nChoose a letter: ";
	if (gameChoice == 1) {
		cin >> *(&pChosenLetters[counter]);
	}
	else {
		*(&pChosenLetters[counter]) = randomInput(pGeneratedLetters);
		cout << *(&pChosenLetters[counter]) << endl;
		Sleep(1000);//comment this if it wont compile on linux
	}

	checkDesignatedWord(*(&pChosenLetters[counter]), pOfDesignatedWord, numberOfLetters, pStage, attempts);
	counter++;
	cout << endl << endl;
}

void fillWithUnderscores(char * pStart, const size_t numberOfLetters) {
	for (int i = 0; i < int(numberOfLetters); i++) {
		*(pStart + i) = '_';
	}
}

void fillWithZeroes(char * pStart, const size_t numberOfLetters) {
	for (int i = 0; i < numberOfLetters; i++)
		*(pStart + i) = 0;
}

void printWordProgress(const char * pStage, const size_t numberOfLetters) {
	for (int i = 0; i < numberOfLetters; i++) {
		cout << *(pStage + i) << " ";
	}
	cout << "   ";
}

void printHistory(const char * pChosenLetters, const size_t lengthOfChosenLettersArray) {
	cout << "History: ";
	for (int i = 0; i < lengthOfChosenLettersArray; i++) {
		if (*(&pChosenLetters[i]) == '\0') {
			return;
		}
		cout << *(&pChosenLetters[i]) << " ";
	}
}

void checkDesignatedWord(char chosenLetter, const char * pOfDesignatedWord, const size_t numberOfLetters, char * pStage, int &attempts) {
	bool flag = false;
	for (int i = 0; i < numberOfLetters; i++) {
		if (chosenLetter == *(pOfDesignatedWord + i)) {
			*(pStage + i) = chosenLetter;
			flag = true;
		}
	}
	if (flag) {
		cout << "OK\n\n";
	}
	else {
		cout << "No such letter!\n\n";
		attempts++;
	}
}

bool underscoresRemain(const char * pStage, const size_t length) {
	for (int i = 0; i < length; i++) {
		if (*(pStage + i) == '_') {
			return true;
		}
	}
	return false;
}

char randomInput(char * pGeneratedLetters) {
	static int index;
	char letter;
	do {
		letter = 97 + rand() % ((122 + 1) - 97);
		pGeneratedLetters[index] = letter;
	} while (letterAlreadySelected(*(pGeneratedLetters + index), pGeneratedLetters, index));
	index++;
	return letter;
}

bool letterAlreadySelected(const char letter, const char * pGeneratedLetters, const size_t index) {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if ((pGeneratedLetters[i] == letter) && (index != i)) {
			return true;
		}
		if (pGeneratedLetters[i] == '_') {
			return false;
		}
	}
	return false;
}

char getMistakesChoice() {
	char mistakesChoice;
	cout << "Maximum mistakes is 5. Would you like to change it (y/n): ";
	do cin >> mistakesChoice;
	while (mistakesChoice != 'n' && mistakesChoice != 'y');
	if (mistakesChoice == 'y') {
		do {
			cout << "Enter new maximum mistakes count: ";
			cin >> maximumMistakes;
			if (maximumMistakes < 0) cout << "ERROR NEGATIVE INPUT\n";
		} while (maximumMistakes < 0);
	}
	return mistakesChoice;
}

int getGameChoice() {
	int gameChoice;
	cout << "\nGuess the word (max " << maximumMistakes << " mistakes)\n";
	cout << "1. Play game" << endl;
	cout << "2. Watch computer play" << endl;
	do cin >> gameChoice;
	while (gameChoice != 1 && gameChoice != 2);
	return gameChoice;
}

void printResult(char * pStage, int numberOfLetters, const char * words[], int attempts, int selectedNumberIndex) {
	if (!underscoresRemain(pStage, numberOfLetters)) {
		cout << "You win!!\nSelected word was: " << words[selectedNumberIndex] << endl;
	}
	if (attempts > maximumMistakes) {
		cout << "You lose!!\nSelected word was: " << words[selectedNumberIndex] << endl;
	}
}

void startGameLoop(int numberOfLetters, const char * pOfDesignatedWord, char * pStage, int &attempts, char * pChosenLetters, int lengthOfChosenLettersArray, char * pGeneratedLetters, int gameChoice) {
	do printCurrentStage(numberOfLetters, pOfDesignatedWord, attempts, pStage, pChosenLetters, lengthOfChosenLettersArray, pGeneratedLetters, gameChoice);
	while ((attempts <= maximumMistakes) && (underscoresRemain(pStage, numberOfLetters)));
}
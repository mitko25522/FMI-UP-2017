#include <iostream>
#include <time.h>

using namespace std;

int getNumberOfHeadings();
int selectObject(const char *objsubj[], int objsubjCount);
int selectSubject(const char *objsubj[], int objsubjCount);
bool isSubject(const char * objsubj);
bool isObject(const char * objsubj);
void printHeading(const char * selectedInterjection,
	const char * selectedObject,
	const char * selectedSubject,
	const char * selectedAction,
	int numberOfExlamationMarks);

#define SPACES_NEEDED 3

int main() {
	srand(time(NULL));

	//objsubj template is ****XY, where **** is the word, X determines if the word is an object,
	//Y determines if the word is a subject (0 for no / 1 for yes)
	const char * interjection[] = { "SHOK", "SKANDAL", "NEVIJDANO DOSEGA", "Nechuvana naglost", "Neveroyatno chudo", "Pulen apsurd", "ironiya" };
	const char * objsubj[] = { "ryapa10", "baba10", "kmeta11", "bager11", "sklad10", "boksior11" };
	const char * action[] = { "sgazi", "zadiga", "namiga na", "precakva", "tarashi", "vze zdraveto na", "potroshi"};
	int interjectionsCount = sizeof(interjection) / sizeof(*interjection);
	int objsubjCount = sizeof(objsubj) / sizeof(*objsubj);
	int actionCount = sizeof(action) / sizeof(*action);
	int numberOfHeadings = getNumberOfHeadings();
	for (int i = 0; i < numberOfHeadings; i++) {
		int selectedInterjectionIndex = rand() % sizeof(interjection) / sizeof(*interjection);
		int selectedObjectIndex = selectObject(objsubj, objsubjCount);
		int selectedSubjectIndex;
		do {
			selectedSubjectIndex = selectSubject(objsubj, objsubjCount);
		} while (selectedSubjectIndex == selectedObjectIndex);
		int selectedActionIndex = rand() % sizeof(action) / sizeof(*action);
		int numberOfExclamationMarks = rand() % (10 - 3 + 1) + 3;
		printHeading(interjection[selectedInterjectionIndex],
			objsubj[selectedObjectIndex],
			objsubj[selectedSubjectIndex],
			action[selectedActionIndex],
			numberOfExclamationMarks);
	}
	cout << endl;
	return 0;
}

int selectObject(const char * objsubj[], int objsubjCount) {
	int index;
	do {
		index = rand() % objsubjCount;
	} while (!isObject(objsubj[index]));
	return index;
}

int selectSubject(const char * objsubj[], int objsubjCount) {
	int index;
	do {
		index = rand() % objsubjCount;
	} while (!isSubject(objsubj[index]));
	return index;
}

bool isSubject(const char * objsubj) {
	int length = 0;
	while (objsubj[length] != 0) {
		length++;
	}
	if (objsubj[length - 1] == '1') {
		return true;
	}
	else {
		return false;
	}
}

bool isObject(const char * objsubj) {
	int length = 0;
	while (objsubj[length] != 0) {
		length++;
	}
	if (objsubj[length - 2] == '1') {
		return true;
	}
	else {
		return false;
	}
}

void printHeading(const char * selectedInterjection,
	const char * selectedObject,
	const char * selectedSubject,
	const char * selectedAction,
	int numberOfExclamationMarks)
{
	int lengthOfInterjection = 0;
	while (selectedInterjection[lengthOfInterjection] != '\0')
		lengthOfInterjection++;

	int lengthOfObject = 0;
	while (selectedObject[lengthOfObject] != '1' && selectedObject[lengthOfObject] != '0')
		lengthOfObject++;

	int lengthOfAction = 0;
	while (selectedAction[lengthOfAction] != '\0')
		lengthOfAction++;

	int lengthOfSubject = 0;
	while (selectedSubject[lengthOfSubject] != '1' && selectedSubject[lengthOfSubject] != '0')
		lengthOfSubject++;

	int sizeOfHeading = lengthOfInterjection + numberOfExclamationMarks + lengthOfSubject + lengthOfAction + lengthOfObject + SPACES_NEEDED;
	char * heading = new (nothrow) char[sizeOfHeading];
	cout << endl << endl;

	for (int i = 0; i < lengthOfInterjection; i++) {
		heading[i] = selectedInterjection[i];
	}

	for (int i = lengthOfInterjection; i < lengthOfInterjection + numberOfExclamationMarks; i++) {
		heading[i] = '!';
	}

	heading[lengthOfInterjection + numberOfExclamationMarks] = ' ';

	for (int i = lengthOfInterjection + numberOfExclamationMarks + 1, j = 0; i < lengthOfInterjection + numberOfExclamationMarks + 1 + lengthOfSubject; i++, j++) {
		heading[i] = selectedSubject[j];
	}

	heading[lengthOfInterjection + numberOfExclamationMarks + 1 + lengthOfSubject] = ' ';

	for (int i = lengthOfInterjection + numberOfExclamationMarks + 1 + lengthOfSubject + 1, j = 0; i < lengthOfInterjection + numberOfExclamationMarks + 1 + lengthOfSubject + 1 + lengthOfAction; i++, j++) {
		heading[i] = selectedAction[j];
	}

	heading[lengthOfInterjection + numberOfExclamationMarks + 1 + lengthOfSubject + 1 + lengthOfAction] = ' ';

	for (int i = lengthOfInterjection + numberOfExclamationMarks + 1 + lengthOfSubject + 1 + lengthOfAction + 1, j = 0; i < lengthOfInterjection + numberOfExclamationMarks + 1 + lengthOfSubject + 1 + lengthOfAction + 1 + lengthOfObject; i++, j++) {
		heading[i] = selectedObject[j];
	}

	for (int i = 0; i < sizeOfHeading; i++) {
		cout << heading[i];
	}
	delete[] heading;
}

int getNumberOfHeadings() {
	int numberOfHeadings;
	cout << "Number of headings: ";
	cin >> numberOfHeadings;
	return numberOfHeadings;
}
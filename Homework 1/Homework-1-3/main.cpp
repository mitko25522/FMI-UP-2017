#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
using namespace std;

int myHealth = 100;
int myDamage = 10;
int myCurrentAttack = 0;
bool didIDefend;
int myArmor = 5;
int myLuck = 5;
int myPotion = 5;
int monsterHealth = 50;
int monsterDamage = 5;
int monsterCurrentAttack = 0;
int monsterArmor = 5;
int monsterLuck = 0;
int gameCoin = 1;
int gameCoinCounter = 0;
int currentLevel = 1;
int monsterHealthBeforeFight=50;
int myHealthBeforeFight = 100;
int numberOfStatsIncreased = 0;
void playerTurn();
void increaseStats() {
	system("cls");
	char input;
	while (::numberOfStatsIncreased < 5) {
		cout << "Your stats \n";
		cout << "Health: " << ::myHealth << endl;
		cout << "Armor: " << ::myArmor << endl;
		cout << "Damage: " << ::myDamage << endl;
		cout << "Luck: " << ::myLuck << endl;
		cout << "Potions: " << ::myPotion << endl;
		cout << "----------------------------------\n";
		cout << "Increase your attributes:\n--(H) health\n--(D) damage\n--(A) armor\n--(L) luck\n";
		cin >> input;
		switch (input) {
		case ('h'): {
			::myHealth++;
			cout << "You have increased your health by one making it " << ::myHealth << endl;
			::numberOfStatsIncreased++;
			cout << 5 - numberOfStatsIncreased << " more stats to increase\n";
			system("pause");
			system("cls");
			break;
			}
		case ('H'): {
			::myHealth++;
			cout << "You have increased your health by one making it " << ::myHealth << endl;
			::numberOfStatsIncreased++;
			cout << 5 - numberOfStatsIncreased << " more stats to increase\n";
			system("pause");
			system("cls");
			break;
		}
		case ('d'): {
			::myDamage++;
			cout << "You have increased your damage by one making it " << ::myDamage << endl;
			::numberOfStatsIncreased++;
			cout << 5 - numberOfStatsIncreased << " more stats to increase\n";
			system("pause");
			system("cls");
			break;
		}
		case ('D'): {
			::myDamage++;
			cout << "You have increased your damage by one making it " << ::myDamage << endl;
			::numberOfStatsIncreased++;
			cout << 5 - numberOfStatsIncreased << " more stats to increase\n";
			system("pause");
			system("cls");
			break;
		}
		case ('a'): {
			::myArmor++;
			cout << "You have increased your armor by one making it " << ::myArmor << endl;
			::numberOfStatsIncreased++;
			cout << 5 - numberOfStatsIncreased << " more stats to increase\n";
			system("pause");
			system("cls");
			break;
		}
		case ('A'): {
			::myArmor++;
			cout << "You have increased your armor by one making it " << ::myArmor << endl;
			::numberOfStatsIncreased++;
			cout << 5 - numberOfStatsIncreased << " more stats to increase\n";
			system("pause");
			system("cls");
			break;
		}
		case ('l'): {
			::myLuck++;
			cout << "You have increased your luck by one making it " << ::myLuck << endl;
			::numberOfStatsIncreased++;
			cout << 5 - numberOfStatsIncreased << " more stats to increase\n";
			system("pause");
			system("cls");
			break;
		}
		case ('L'): {
			::myLuck++;
			cout << "You have increased your luck by one making it " << ::myLuck << endl;
			::numberOfStatsIncreased++;
			cout << 5 - numberOfStatsIncreased << " more stats to increase\n";
			system("pause");
			system("cls");
			break;
		}
		default: {
			increaseStats();
			break;
		}
		}
	}
}
void resetAllValues() {
	myHealth = 100;
	myDamage = 10;
	myCurrentAttack = 0;
	myArmor = 5;
	myLuck = 5;
	myPotion = 5;
	monsterHealth = 50;
	monsterDamage = 5;
	monsterCurrentAttack = 0;
	monsterArmor = 5;
	monsterLuck = 0;
	gameCoinCounter = 0;
	currentLevel = 1;
	monsterHealthBeforeFight = 50;
	myHealthBeforeFight = 100;
}
void didPlayerGetPotion() {
	int chance = rand() % 10 + 1;
	if (chance < 6) {
		myPotion++;
	}
	cout << "You received a bonus potion\n";
}
int isPlayerLucky() {
	int myChance = ::myLuck*0.5;
	int randomZeroToHundred = rand() % 101;
	if (randomZeroToHundred >= myChance) {
		return 2;
	}
	return 1;
	//isPlayerLucky returns 1 if player is Lucky
	//else returns 2 if player is unlucky
}
int isMonsterLucky() {
	int monsterChance = ::monsterLuck*0.5;
	int randomZeroToHundred = rand() % 101;
	if (randomZeroToHundred >= monsterChance) {
		return 2;
	}
	return 1;
	//isMonsterLucky returns 1 if monster is Lucky
	//else returns 2 if monster is unlucky
}
void monsterAttack() {
	if (isMonsterLucky() == 2) {
		::monsterCurrentAttack = ::monsterDamage - ((0.5*::myArmor) / 100)*::monsterDamage;
		::myHealth -= monsterCurrentAttack;
		cout << "---Monster attacked you leaving you with " << ::myHealth << " Health\n";
	}
	else if (isMonsterLucky() == 1) {
		::monsterCurrentAttack = (::monsterDamage - ((0.5*::myArmor) / 100)*::monsterDamage) * 2;
		::myHealth -= monsterCurrentAttack;
		cout << "---Monster was lucky when attacking you and did twice the damage leaving you with " << ::monsterHealth << " Health\n";
	}
}
void monsterDefend() {
	int divisor = isMonsterLucky();
	if ((monsterHealth + ::myCurrentAttack / divisor) <= ::monsterHealthBeforeFight) {
		::monsterHealth += ::myCurrentAttack / divisor;
		if (divisor == 2)
			cout << "---Monster defended himself from the previous hit leaving him with " << ::monsterHealth << " Health" << endl;
		else if (divisor == 1)
			cout << "---Monster was lucky and fully defended himself from your previous attack leaving him with " << ::monsterHealth << " Health" << endl;
	}
	else
		::monsterHealth = ::monsterHealthBeforeFight;
}
bool startScreen() {
	char input;
	cout << " Welcome to *name of game*. Please enter your choice:\n\n   Y to start game\n   H for help\n   X to close game\n";
	cout << "\nYou have " << ::gameCoin << " game coins left.\n";
	cin >> input;
	switch (input) {
	case('y'): {
		if (::gameCoin >= 1) {
			cout << "Starting game";
			//Sleep(400);
			cout << ".";
			//Sleep(400);
			cout << ".";
			//Sleep(400);
			cout << ".";
			Sleep(400);
			cout << ".";
			Sleep(400);
			system("cls");
			::gameCoin--;
			return 1;
			break;
		}
		else {
			system("cls");
			cout << "You do not have any coins left.\n\nPurchase coins\n";
			system("pause");
			system("cls");
			return 0;
			break;
		}
	}
	case('Y'): {
		if (::gameCoin >= 1) {
			cout << "Starting game";
			//Sleep(400);
			cout << ".";
			//Sleep(400);
			cout << ".";
			//Sleep(400);
			cout << ".";
			Sleep(400);
			cout << ".";
			Sleep(400);
			system("cls");
			::gameCoin--;
			return 1;
			break;
		}
		else {
			system("cls");
			cout << "You do not have any coins left.\n\nPurchase coins\n";
			system("pause");
			system("cls");
			return 0;
			break;
		}
	}
	case('h'): {
		system("cls");
		cout << "Your main goal is to fight monsters that get more powerful as you progress through\nthe stages.\nYou have four attributes Health, Damage, Armor and Luck\nHealth - You start with 100 Health points and upon reaching 0 the game ends and you are\ngiven the choice of using a Game Coin to try again or if you do not have any you can\npurchase them with bitcoins\nDamage - The value of Damage determines how much health points are reduced\nArmor - Each Armor point reduces the Damage inflicted by 0.5%\nLuck - Each Luck point increases your chances by 0.5% of inflicting a double hit or \nto fully avoid getting hit when defending yourself.\nUsable item Potion - Instead of attacking you can use a Potion which will restore\nyour Health to it's maximum value\n\nEach turn the player must choose between attacking, defending himself or using a Potion.\nAfter successfully defending himself the player reduces the damage caused to him by 50 % \nWhen you kill a monster you have a 50 % chance of finding a Potion and you also\ngain 5 points which you can allocate between your attributes increasing their maximum\nvalue.Each following monster has his attributes increased by 2 points\nYou get a Game Coin for each 5 monsters slain.\n";
		system("pause");
		system("cls");
		return 0;
		break;
	}
	case('H'): {
		system("cls");
		cout << "Your main goal is to fight monsters that get more powerful as you progress through\nthe stages.\nYou have four attributes Health, Damage, Armor and Luck\nHealth - You start with 100 Health points and upon reaching 0 the game ends and you are\ngiven the choice of using a Game Coin to try again or if you do not have any you can\npurchase them with bitcoins\nDamage - The value of Damage determines how much health points are reduced\nArmor - Each Armor point reduces the Damage inflicted by 0.5%\nLuck - Each Luck point increases your chances by 0.5% of inflicting a double hit or \nto fully avoid getting hit when defending yourself.\nUsable item Potion - Instead of attacking you can use a Potion which will restore\nyour Health to it's maximum value\n\nEach turn the player must choose between attacking, defending himself or using a Potion.\nAfter successfully defending himself the player reduces the damage caused to him by 50 % \nWhen you kill a monster you have a 50 % chance of finding a Potion and you also\ngain 5 points which you can allocate between your attributes increasing their maximum\nvalue.Each following monster has his attributes increased by 2 points\nYou get a Game Coin for each 5 monsters slain.\n";
		system("pause");
		system("cls");
		return 0;
		break;
	}
	case('x'): {
		exit(0);
		break;
	}
	case('X'): {
		exit(0);
		break;
	}


	default: {
		system("cls");
		return 0;
	}
	}
}
void printInformation() {
	system("cls");
	cout << "Level " << ::currentLevel << endl;
	cout << "----------------------------------\n";
	cout << "Your stats \n";
	cout << "Health: " << ::myHealth << endl;
	cout << "Armor: " << ::myArmor << endl;
	cout << "Damage: " << ::myDamage << endl;
	cout << "Luck: " << ::myLuck << endl;
	cout << "Potions: " << ::myPotion << endl;
	cout << "----------------------------------\n";
	cout << "Enemy stats \n";
	cout << "Health: " << ::monsterHealth << endl;
	cout << "Armor: " << ::monsterArmor << endl;
	cout << "Damage: " << ::monsterDamage << endl;
	cout << "Luck: " << ::monsterLuck << endl;
	cout << "----------------------------------\n";
	if (gameCoin < 1) {
		cout << "\nYou currently do not have any game coins left.\n\n";
	}
	else
	{
		cout << "\nYou currently have " << gameCoin << " gamecoins\n\n";
	}

}
void encounterMonster() {
	cout << "You currently have " << gameCoin << " gamecoins\n";
	cout << "Level " << ::currentLevel << " A wild monster attacked you. \n" << endl;
	cout << "Your attributes are: Health " << ::myHealth << ", Armor " << ::myArmor << ", Damage " << ::myDamage << ", Luck " << ::myLuck << endl;
	cout << "You have " << myPotion << " potions left\n";
	cout << "His attributes are: Health " << ::monsterHealth << ", Armor " << ::monsterArmor << ", Damage " << ::monsterDamage << ", Luck " << ::monsterLuck << endl;
}
void playerAttack() {
	if (isPlayerLucky() == 2) {
		::myCurrentAttack = ::myDamage - ((0.5*::monsterArmor) / 100)*::myDamage;
		::monsterHealth -= myCurrentAttack;
		cout << "---You attacked the enemy leaving him with " << ::monsterHealth << " Health\n";
	}
	else if (isPlayerLucky() == 1) {
		::myCurrentAttack = (::myDamage - ((0.5*::monsterArmor) / 100)*::myDamage) * 2;
		::monsterHealth -= myCurrentAttack;
		cout << "---You were lucky when attacking the enemy and did twice the damage leaving him with " << ::monsterHealth << " Health\n";
	}
}
void playerDefend() { 
	 if (isPlayerLucky()==1) {
		 cout << "---You were lucky when defending yourself and will fully ignore monster's next hit\n";
		 ::didIDefend = 1;
	 }
	 else {
		 cout << "---You will defend yourself from the next attack and take half damage\n";
		 ::didIDefend = 2;
	 }
}
void playerUsePotion() {
	if (myPotion > 0) {
		myPotion--;
		::myHealth = ::myHealthBeforeFight;
		cout << "---You have successfully used a potion replenishing your Health fully to " << ::myHealth << endl;
		myCurrentAttack = 0;
	}
	else {
		cout << "---Insufficient amount potions\n";
		system("pause");
		system("cls");
		encounterMonster();
		playerTurn();
	}
}
void playerTurn() {
	char input;
	cout << "\n\nWould you like to show Information(I), Attack(A), Defend(D), use Potion(P) or exit game(X): ";
	cin >> input;
	switch (input) {
	case('a'): {
		playerAttack();
		break;
	}
	case('A'): {
		playerAttack();
		break;
	}
	case('d'): {
		playerDefend();
		break;
	}
	case('D'): {
		playerDefend();
		break;
	}
	case('p'): {
		playerUsePotion();
		break;
	}
	case('P'): {
		playerUsePotion();
		break;
	}
	case('x'): {
		exit(0);
		break;
	}
	case('X'): {
		exit(0);
		break;
	}
	case('i'): {
		printInformation();
		system("pause");
		system("cls");
		encounterMonster();
		playerTurn();
		break;
	}
	case('I'): {
		printInformation();
		system("pause");
		system("cls");
		encounterMonster();
		playerTurn();
		break;
	}
	default: {
		cout << "Invalid input\n";
		system("pause");
		system("cls");
		encounterMonster();
		playerTurn();
		break;
	}
	}

}
void monsterTurn() {
	int choice = rand() % 10 + 1;
	if (::didIDefend == 2) {
		cout << "---Monster's attack was ineffective and did zero damage\n";
		didIDefend = 0;
	}else if (::didIDefend == 1) {
		::monsterCurrentAttack = (::monsterDamage - ((0.5*::myArmor) / 100)*::monsterDamage)/2;
		::myHealth -= monsterCurrentAttack;
		cout << "---Monster attacked you but you blocked half the damage leaving you with " << ::myHealth << " Health\n";
		didIDefend = 0;
	}else if (choice <= 4 || myCurrentAttack == 0 ) {
		monsterAttack();
	}else if (choice > 4){
		monsterDefend();
	}
	
}
void retryScreen() {
}
bool didILoseTheFight() {
	::monsterHealthBeforeFight = ::monsterHealth;
	::myHealthBeforeFight = ::myHealth;
	while (monsterHealth> 0) {
		if (myHealth <= 0) {
			system("cls");
			cout << "You were defeated by the monster\n";
			resetAllValues();
			system("pause");
			system("cls");
			return 0;
		}
		system("pause");
		system("cls");
		encounterMonster();
		playerTurn();
		//Sleep(1000);
		monsterTurn();
		//Sleep(1000);


	}
	cout << "Congratulations you defeated the monster. Now you are progressing to level number " << currentLevel + 1 << endl << endl;
	::monsterHealth = ::monsterHealthBeforeFight;
	::myHealth = ::myHealthBeforeFight;
	didPlayerGetPotion();
	system("pause");
	::numberOfStatsIncreased = 0;
	increaseStats();
	system("cls");
	return 1;

}
void progressToNextMonster() {
	::currentLevel++;
	::monsterHealth += 2;
	::monsterDamage += 2;
	::monsterArmor += 2;
	::monsterLuck += 2;
	::gameCoinCounter++;
	if (::gameCoinCounter == 5) {
		::gameCoin += 1;
		::gameCoinCounter = 0;
	}
}
int playGame() {
	while (startScreen() == 0) {}
	encounterMonster();
	while (didILoseTheFight() != 0) {
		progressToNextMonster();
		encounterMonster();
	}
	return 0;
}

int main()
{
	srand(time(NULL));
	while (playGame() == 0) {}
	return 0;
}

//to do list:
//implement printInformation() ----------------------------------------------------------------------
//fix printInformation() problems becouse it messes up future input after being used-----------------
//implement isMonsterLucky() to monsterAttack()------------------------------------------------------
//implement playerDefend() with isPlayerLucky()------------------------------------------------------
//add purchase game coins option when none are available
//create menu to increase attributes upon killing a monster------------------------------------------
//add 50% chance to receive a Potion upon killing a monster with didPlayerGetPotion()----------------
//implement option to start new game with 1 game coin------------------------------------------------


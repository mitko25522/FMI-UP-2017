#include "Definitions.h"
#include "UI.hpp"
#include <iostream>
#include <math.h>

using namespace std;
void printLog(double input[]);


int main()
{
    double gameData[1000];
	GetInput(gameData);
	gameData[0] = 583; //redefine incorrect gameData
	gameData[1] = 360;

	GameRoomBoundary gameRoomBoundary;
	gameRoomBoundary.left.start.x = 0;
	gameRoomBoundary.left.start.y = 0;
	gameRoomBoundary.left.end.x = 0;
	gameRoomBoundary.left.end.y = gameData[HEIGHT_OF_GAMEROOM];

	gameRoomBoundary.right.start.x = gameData[WIDTH_OF_GAMEROOM];
	gameRoomBoundary.right.start.y = 0;
	gameRoomBoundary.right.end.x = gameData[WIDTH_OF_GAMEROOM];
	gameRoomBoundary.right.end.y = gameData[HEIGHT_OF_GAMEROOM];
	
	gameRoomBoundary.upper.start.x = 0;
	gameRoomBoundary.upper.start.y = 0;
	gameRoomBoundary.upper.end.x = gameData[WIDTH_OF_GAMEROOM];
	gameRoomBoundary.upper.end.y = 0;

	gameRoomBoundary.bottom.start.x = 0;
	gameRoomBoundary.bottom.start.y = gameData[HEIGHT_OF_GAMEROOM];
	gameRoomBoundary.bottom.end.x = gameData[WIDTH_OF_GAMEROOM];
	gameRoomBoundary.bottom.end.y = gameData[HEIGHT_OF_GAMEROOM];

	Line userInitialRay;
	userInitialRay.start.x = gameData[USER_SELECTED_START_X];
	userInitialRay.start.y = gameData[USER_SELECTED_START_Y];
	userInitialRay.end.x = gameData[USER_SELECTED_TOWARDS_X]; //initially we assign the end of 
	userInitialRay.end.y = gameData[USER_SELECTED_TOWARDS_Y]; //the ray to the user's choice of direction

	Line mirrorOne, mirrorTwo, mirrorThree;
	mirrorOne.start.x = gameData[MIRROR_ONE_FROM_X];
	mirrorOne.start.y = gameData[MIRROR_ONE_FROM_Y];
	mirrorOne.end.x = gameData[MIRROR_ONE_TO_X];
	mirrorOne.end.y = gameData[MIRROR_ONE_TO_Y];
	
	mirrorTwo.start.x = gameData[MIRROR_TWO_FROM_X];
	mirrorTwo.start.y = gameData[MIRROR_TWO_FROM_Y];
	mirrorTwo.end.x = gameData[MIRROR_TWO_TO_X];
	mirrorTwo.end.y = gameData[MIRROR_TWO_TO_Y];

	mirrorThree.start.x = gameData[MIRROR_THREE_FROM_X];
	mirrorThree.start.y = gameData[MIRROR_THREE_FROM_Y];
	mirrorThree.end.x = gameData[MIRROR_THREE_TO_X];
	mirrorThree.end.y = gameData[MIRROR_THREE_TO_Y];

	Target target;
	target.location.x = gameData[TARGET_X_COORDINATE];
	target.location.y = gameData[TARGET_Y_COORDINATE];
	target.radius = gameData[TARGET_RADIUS];


	Point reflection = pointOfIntersection(userInitialRay, mirrorOne);
	if ((reflection.x == -1) && (reflection.y == -1))
		reflection = pointOfIntersection(userInitialRay, mirrorTwo);
	if ((reflection.x == -1) && (reflection.y == -1))
		reflection = pointOfIntersection(userInitialRay, mirrorThree);
	cout << "First reflection at (" << reflection.x << "," << reflection.y << ")\n";
	SetRaySegment(userInitialRay.end.x, userInitialRay.end.y, reflection.x, reflection.y);
	cout << "Angle between user's initial ray and mirror three is "<<angleBetweenLines(userInitialRay, mirrorThree)<<"degrees"<<endl;
	Line reflectedRay;
	reflectedRay.start.x = reflection.x;
	reflectedRay.start.y = reflection.y;
	reflectedRay.end.x = reflectedRay.start.x + (2 * cos(angleBetweenLines(userInitialRay, mirrorThree)));
	printLog(gameData);
	SetRaySegment(reflection.x,reflection.y, reflectedRay.start.y, -reflectedRay.end.y);
    return 0;
}

void printLog(double input[]) {
	cout << "User selected starting point of ray at (" << input[USER_SELECTED_START_X] << "," << input[USER_SELECTED_START_Y] << ") towards (" << input[USER_SELECTED_TOWARDS_X] << "," << input[USER_SELECTED_TOWARDS_Y] << ")\n";
	cout << "Mirror one has coordinates of (" << input[MIRROR_ONE_FROM_X] << "," << input[MIRROR_ONE_FROM_Y] << ") to (" << input[MIRROR_ONE_TO_X] << "," << input[MIRROR_ONE_TO_Y] << ")\n";
	cout << "Mirror two has coordinates of (" << input[MIRROR_TWO_FROM_X] << "," << input[MIRROR_TWO_FROM_Y] << ") to (" << input[MIRROR_TWO_TO_X] << "," << input[MIRROR_TWO_TO_Y] << ")\n";
	cout << "Mirror three has coordinates of (" << input[MIRROR_THREE_FROM_X] << "," << input[MIRROR_THREE_FROM_Y] << ") to (" << input[MIRROR_THREE_TO_X] << "," << input[MIRROR_THREE_TO_Y] << ")\n";
	cout << "Game room is " << input[WIDTH_OF_GAMEROOM] << " by " << input[HEIGHT_OF_GAMEROOM] << "\n";
}
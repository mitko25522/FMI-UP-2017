#pragma once
#include <iostream>//for debugging
#include <cmath>
using namespace std;
#define WIDTH_OF_GAMEROOM  0
#define HEIGHT_OF_GAMEROOM 1
#define TARGET_X_COORDINATE 2
#define TARGET_Y_COORDINATE 3
#define TARGET_RADIUS 4
#define USER_SELECTED_START_X 5
#define USER_SELECTED_START_Y 6
#define USER_SELECTED_TOWARDS_X 7
#define USER_SELECTED_TOWARDS_Y 8
#define MAX_REFLECTIONS 9
#define NUMBER_OF_MIRRORS 10
#define MIRROR_ONE_FROM_X 11 
#define MIRROR_ONE_FROM_Y 12
#define MIRROR_ONE_TO_X 13
#define MIRROR_ONE_TO_Y 14
#define MIRROR_TWO_FROM_X 15
#define MIRROR_TWO_FROM_Y 16
#define MIRROR_TWO_TO_X 17
#define MIRROR_TWO_TO_Y 18
#define MIRROR_THREE_FROM_X 19
#define MIRROR_THREE_FROM_Y 20
#define MIRROR_THREE_TO_X 21
#define MIRROR_THREE_TO_Y 22
#define _USE_MATH_DEFINES
#include <math.h>

struct Point
{
	double x=0;
	double y=0;
};

double findDistanceBetweenPoints(Point one, Point two);
typedef Point Slope;

struct Line
{
	Point start;
	Point end;

	double slope(Line line) {
		Slope slope;
		slope.x = line.end.x - line.start.x;
		slope.y = line.end.y - line.start.y;
		double Slope = slope.y / slope.x;
		return Slope;
	}

	bool containsPoint(Line line, Point inputPoint) {
		for (double modifier = 0; modifier <= 1; modifier += 0.0001)
		{
			Point currentPointOfLine;
			//walk through all the points on the line
			currentPointOfLine.x = line.start.x + modifier*(line.end.x - line.start.x);
			currentPointOfLine.y = line.start.y + modifier*(line.end.y - line.start.y);
			double distanceBetweenPoints = findDistanceBetweenPoints(inputPoint, currentPointOfLine);
			//check if our inputPoint achieves the needed proximity to the currentPointOfLine
			if (distanceBetweenPoints < 1) {
				return true;
			}
			
			if ((currentPointOfLine.x > 600)||(currentPointOfLine.y>400)) {
				return false;
			}
		}
	}
};

double findDistanceBetweenPointAndMirror(Point point, Line line);

Line LineMake(Point start, Point end) {
	Line line;
	line.start = start;
	line.end = end;
	return line;
}

struct GameRoomBoundary
{
	Line left;
	Line right;
	Line upper;
	Line bottom;
	//GameRoomBoundary GameRoomBoundaryМаке(Line left, Line right, Line upper, Line bottom) {
	//	GameRoomBoundary gameRoomBoundary;
	//	gameRoomBoundary.left = left;
	//	gameRoomBoundary.right = right;
	//	gameRoomBoundary.upper = upper;
	//	gameRoomBoundary.bottom = bottom;
	//	return gameRoomBoundary;
	//}
};

struct Target
{
	Point location;
	double radius;
};



//must find two different times the distance between the ray and mirror to determine whether or not the ray is approaching the certain mirror
Point pointOfIntersection(Line ray, Line line) {
	Point currentPointOfRay;
	for (double offset = 1.01; !line.containsPoint(line, currentPointOfRay); offset += 0.01) {
		double initialDistance = findDistanceBetweenPointAndMirror(ray.end, line);
		currentPointOfRay.x = ray.start.x + offset*(ray.end.x - ray.start.x);
		currentPointOfRay.y = ray.start.y + offset*(ray.end.y - ray.start.y);
		double secondDistance = findDistanceBetweenPointAndMirror(currentPointOfRay, line);
		//cout << "Distance between ray and mirror " << secondDistance << endl;
		if (initialDistance < secondDistance) {
			currentPointOfRay.x = -1;
			currentPointOfRay.y = -1;
			return currentPointOfRay;
		}
	}
	return currentPointOfRay;
}

double findDistanceBetweenPoints(Point one, Point two) {
	double xDifference = one.x - two.x;
	double yDifference = one.y - two.y;
	xDifference = (xDifference < 0) ? xDifference * (-1) : xDifference;
	yDifference = (yDifference < 0) ? yDifference * (-1) : yDifference;
	double distanceBetweenPoints = sqrt(xDifference*xDifference + yDifference*yDifference);
	return distanceBetweenPoints;
}

double findDistanceBetweenPointAndMirror(Point point, Line line) {
	double minimumDistance = 1000;
	for (double modifier = 0; modifier <= 1; modifier += 0.001)
	{
		Point currentPointOfLine;
		//walk through all the points on the line
		currentPointOfLine.x = line.start.x + modifier*(line.end.x - line.start.x);
		currentPointOfLine.y = line.start.y + modifier*(line.end.y - line.start.y);
		//find smallest distance between the point and all the points on the line
		if(findDistanceBetweenPoints(point, currentPointOfLine)<minimumDistance)
		minimumDistance=findDistanceBetweenPoints(point,currentPointOfLine);
	}
	return minimumDistance;
}
double slope(Line line) {
	Slope slope;
	slope.x = line.end.x - line.start.x;
	slope.y = line.end.y - line.start.y;
	double Slope = slope.y / slope.x;
	return Slope;
}
//double angleBetweenLines(Line lineOne, Line lineTwo) {
//	double result = (atan((lineOne.slope(lineOne)-lineTwo.slope(lineTwo))/1+lineOne.slope(lineOne)*lineTwo.slope(lineTwo) )* 180 / M_PI);
//	return result;
//}

double angleBetweenLines(Line lineOne, Line lineTwo) {
	double result = (atan(slope(lineOne) - slope(lineTwo)) / (1 + slope(lineOne)*slope(lineTwo)) * 180 / M_PI);
	if (result < 0) result *= -1;
	return result;
}
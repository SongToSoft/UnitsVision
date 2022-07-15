#pragma once

#define _USE_MATH_DEFINES

#include "Unit.h"
#include <vector>
#include <cmath>

class Field {
public:
	Field();
	~Field();

	void generateSmall();
	int generateRandom();

	void checkVision(bool isMultithread = true);
	void toggleDebug();
private:
	void checkUnitsVision(size_t start, size_t end);
	void showUnits();

	float getAngle(std::pair<float, float> point1, std::pair<float, float> point2);

	bool checkInCircle(Unit* current, Unit* verifiable);
	bool inSector(float angle);

	std::vector<Unit*> units;
	float sectorAngle = 0.f;
	float distance = 0.f;

	bool debugEnabled = false;
};
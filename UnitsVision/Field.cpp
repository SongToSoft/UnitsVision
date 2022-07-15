#include "Field.h"
#include <thread>
#include <iostream>
#include <functional> 

#define MAX_DISTANCE 100
#define MIN_UNITS 5000
#define MAX_UNITS 10000
#define LOW_DIRECTION -1
#define HIGH_DIRECTION 1

Field::Field() {
}

Field::~Field() {
	for (auto const& unit : units) {
		delete unit;
	}
}

void Field::generateSmall() {
	sectorAngle = 135.5;
	distance = 2;

	Unit* unit0 = new Unit();
	unit0->setPosition({ 1, 1 });
	unit0->setDirection({ 0, 1 });

	Unit* unit1 = new Unit();
	unit1->setPosition({ 1, 2 });
	unit1->setDirection({ 1, 0 });

	Unit* unit2 = new Unit();
	unit2->setPosition({ -5, -1 });
	unit2->setDirection({ 0.707, 0.707 });

	Unit* unit3 = new Unit();
	unit3->setPosition({ 1, -1 });
	unit3->setDirection({ -0.4, 0.5 });

	Unit* unit4 = new Unit();
	unit4->setPosition({ 0, 0 });
	unit4->setDirection({ 0, 1 });

	Unit* unit5 = new Unit();
	unit5->setPosition({ 0, -5 });
	unit5->setDirection({ -1, 0 });

	Unit* unit6 = new Unit();
	unit6->setPosition({ -4, -1 });
	unit6->setDirection({ -1, -1 });

	Unit* unit7 = new Unit();
	unit7->setPosition({ -4, -1 });
	unit7->setDirection({ -1, -1 });

	units.push_back(unit0);
	units.push_back(unit1);
	units.push_back(unit2);
	units.push_back(unit3);
	units.push_back(unit4);
	units.push_back(unit5);
	units.push_back(unit6);
	units.push_back(unit7);
}

int Field::generateRandom() {
	auto unitsCount = MIN_UNITS + (rand() % MAX_UNITS);
	sectorAngle = static_cast<float>(rand() % MAX_DISTANCE);
	distance = static_cast<float>(rand() % unitsCount);

	for (int i = 0; i < unitsCount; ++i) {
		auto unit = new Unit();
		float directionY = LOW_DIRECTION + static_cast<float>(rand()) * static_cast<float>(HIGH_DIRECTION - LOW_DIRECTION) / RAND_MAX;
		float directionX = LOW_DIRECTION + static_cast<float>(rand()) * static_cast<float>(HIGH_DIRECTION - LOW_DIRECTION) / RAND_MAX;
		unit->setDirection({ directionY, directionX });

		float positionX = static_cast<float>(rand()) * static_cast<float>(MAX_UNITS) / RAND_MAX;
		float positionY = static_cast<float>(rand()) * static_cast<float>(MAX_UNITS) / RAND_MAX;
		unit->setPosition({ positionY, positionX });

		units.push_back(unit);
	}
	return unitsCount;
}


void Field::checkVision(bool isMultithread) {
	if (debugEnabled) {
		std::cout << "View Distance: " << distance << ", View Sector Angle: " << sectorAngle << std::endl;
		showUnits();
	}

	if (isMultithread) {
		auto coresCount = std::thread::hardware_concurrency();
		std::vector<std::thread*> threads;
		if (units.size() < coresCount) {
			coresCount = units.size();
		}
		auto threadWork = (units.size() / coresCount);
		auto threadRemainder = units.size() - (threadWork * coresCount);
		for (unsigned int i = 0; i < coresCount; ++i) {
			size_t start = (size_t)(threadWork * i);
			size_t end = (size_t)(threadWork * (i + 1));
			if (i == (coresCount - 1)) {
				end += threadRemainder;
			}
			std::thread* thread = new std::thread(std::bind(&Field::checkUnitsVision, this, start, end));
			threads.push_back(thread);
		}
		for (unsigned int i = 0; i < coresCount; ++i) {
			threads[i]->join();
		}
		for (unsigned int i = 0; i < coresCount; ++i) {
			delete threads[i];
		}
	}
	else {
		checkUnitsVision(0, units.size());
	}
}

void Field::toggleDebug() {
	debugEnabled = !debugEnabled;
}

void Field::checkUnitsVision(size_t start, size_t end) {
	for (size_t i = start; i < end; ++i) {
		std::pair<float, float> centerSectorVec = { units[i]->getDirection().first * distance, units[i]->getDirection().second * distance };
		int visibleCount = 0;
		for (size_t j = 0; j < units.size(); ++j) {
			if (i != j) {
				if (checkInCircle(units[i], units[j])) {
					std::pair<float, float> unitDiffVec = { units[j]->getPosition().first - units[i]->getPosition().first,
															units[j]->getPosition().second - units[i]->getPosition().second };
					auto angle = getAngle(centerSectorVec, unitDiffVec);
					if (!isnan(angle)) {
						if (debugEnabled) {
							std::cout << "Angle between center sector " << "Unit[" << i << "] and Unit[" << j << "]: " << angle << std::endl;
						}
						if (inSector(angle)) {
							++visibleCount;
							if (debugEnabled) {
								std::cout << "Unit[" << i << "] see Unit[" << j << "]" << std::endl;
							}
						}
					}
				}
			}
		}
		if (debugEnabled) {
			std::cout << "Unit[" << i << "] see: " << visibleCount << " units in vision sector" << std::endl;
			std::cout << std::endl;
		}
	}
}

void Field::showUnits() {
	for (size_t i = 0; i < units.size(); ++i) {
		std::cout << "Unit[" << i << "] Position: [" << units[i]->getPosition().first << ", " << units[i]->getPosition().second << "]" <<
			         ", Direction: [" << units[i]->getDirection().first << ", " << units[i]->getDirection().second << "] " << std::endl;
	}
	std::cout << std::endl;
}

bool Field::checkInCircle(Unit* current, Unit* verifiable) {
	auto y = (verifiable->getPosition().first - current->getPosition().first);
	auto x = (verifiable->getPosition().second - current->getPosition().second);
	return ((pow(x, 2) + pow(y, 2)) <= (pow(distance, 2)));
}

float Field::getAngle(std::pair<float, float> positionOne, std::pair<float, float> positionTwo) {
	auto up = positionOne.first * positionTwo.first + positionOne.second * positionTwo.second;
	auto down = sqrt(pow(positionOne.first, 2) + pow(positionOne.second, 2)) *
		        sqrt(pow(positionTwo.first, 2) + pow(positionTwo.second, 2));
	auto angle = static_cast<float>((double)(acos(up/down)) * 180 / M_PI);
	return angle;
}

bool Field::inSector(float angle) {
	return (angle <= (sectorAngle / 2));
}

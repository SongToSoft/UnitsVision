#include <iostream>
#include "Field.h"
#include <ctime>

int main()
{
	Field smallField;
	smallField.generateSmall();
	smallField.toggleDebug();
	smallField.checkVision(false);

	Field randomField;
	auto unitsCount = randomField.generateRandom();

	std::cout << std::endl;
	auto starTtime = clock();
	randomField.checkVision();
	auto endTime = clock();
	auto elapsedTime = endTime - starTtime;
	std::cout << "Elapsed time with multi-thread: " << elapsedTime << " for " << unitsCount << " units " << std::endl;

	starTtime = clock();
	randomField.checkVision(false);
	endTime = clock();
	elapsedTime = endTime - starTtime;
	std::cout << "Elapsed time in one thread: " << elapsedTime << " for " << unitsCount << " units " << std::endl;
}
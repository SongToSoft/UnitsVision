#pragma once

#include <utility>

class Unit {
public:
	Unit();
	~Unit();

	std::pair<float, float> getPosition();
	std::pair<float, float> getDirection();

	void setDirection(std::pair<float, float> _direction);
	void setPosition(std::pair<float, float> _position);
private:
	std::pair<float, float> direction;
	std::pair<float, float> position;
};
#include "Unit.h"

Unit::Unit() {
}

Unit::~Unit() {
}

std::pair<float, float> Unit::getPosition() {
	return position;
}

std::pair<float, float> Unit::getDirection() {
	return direction;
}

void Unit::setDirection(std::pair<float, float> _direction) {
	direction = _direction;
}

void Unit::setPosition(std::pair<float, float> _position) {
	position = _position;
}
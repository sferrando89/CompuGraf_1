#include "Direction.h"

Direction operator++(Direction& d, int) {
	switch (d) {
	case Direction::up:
		d = Direction::right;
		break;
	case Direction::right:
		d = Direction::down;
		break;
	case Direction::down:
		d = Direction::left;
		break;
	case Direction::left:
		d = Direction::up;
		break;
	}
	return d;
}

Direction operator--(Direction& d, int) {
	switch (d) {
	case Direction::up:
		d = Direction::left;
		break;
	case Direction::left:
		d = Direction::down;
		break;
	case Direction::down:
		d = Direction::right;
		break;
	case Direction::right:
		d = Direction::up;
		break;
	}
	return d;
}